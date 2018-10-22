/*========================================================================
 *
 * File:      $RCSfile: InstanceTracker.h,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_instance_tracker_
#define _included_class_instance_tracker_ 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#include <map>
#include <set>
#include <string>
#include <mc_dbms/mc_dbms_types.h>
#include <sstream>
#include <mc_dbms/database.h>
#include <mc_dbms/database_root.h>
#include <mc_dbms/SerializableObject.h>
#include <mc_dbms/persistence.h>
#include <CountedPtr.h>
#include <mc_dbms/typespec.h>

class mc_dbms_database;
class mc_dbms_typespec;
class mc_dbms_segment;
class Persistence;


/**
 * This class keeps track of instance data as it is created and modified.  It 
 * does this by taking advange of the placement-new operaters used by generator.  
 * All of the placement new and placement delete operators are implemented so 
 * that that they call static methods (allocate() and destroy()) inside 
 * InstanceTracker. When allocate() is called, Instance tracker takes the type 
 * of the object (which is passed-in through a mc_dbms_typespec object), and 
 * determines the size needed for the object (also using the mc_dbms_typespec).  
 * InstanceTracker then performs a looked to see if any instances of this type 
 * have been seen before. If instances have been seen, a counter has been 
 * mainted that serves as an instance identifier, and we use that to get a 
 * identifer for the new instance.  Using this information (type, size, 
 * instance id), allocate() then allocates a block of memory for the instance, 
 * creates an object where we store all this instance data (called "Instance"), 
 * and inserts this object into a std::multimap (key  of the map is instance 
 * type, and value is pointer to the "Instance" object). In this way we keep 
 * every instance requested in the generater in-memory.  When operator delete 
 * is called (which calls InstanceTracker::destroy()), we look-up  the 
 * instance to be destroyed (using the type and value of the pointer) and  we 
 * remove it.  
 * <br>
 * InstanceTracker allows callers access to the instance through an accessor  
 * method that returns a const reference to the collection of instances.   
 * <br>
 * InstanceTracker also contains helper functions that can report on all the  
 * data in the collection and persist the data in the collection. 
 * 
 */
class InstanceTracker
{
public:
	friend class TestInstanceTracker;
	friend class Persistence;

	class Instance;
	typedef CountedPtr<Instance> InstancePtr;
	
	/**
	 * This holds data about an object instance. This is used to persist
	 * the instance.
	 */
	class Instance : public SerializableObject 
	{
	public:

		Instance(TrackedType type, int typeSize, int numInstances, long instanceNum, bool isPersisent, char* objPtr = 0);
		virtual ~Instance();
		
		/**
		 * Determine if this instance needs to be serialized or not.
		 */		
		bool needToSerialize() {
			bool serialize = false;
			if (m_persistFlag == Persistence::InitialState) {
				serialize = true;
			}
			return serialize;
		}
		
		virtual long persist();
		static InstancePtr create();
		static long persist(char* blockPtr);

		long m_typeSize;
		bool m_persistent;
		int m_persistFlag;
		TrackedType m_type;
		
		/**
		 * If this is an array of instances then this will
		 * be greater then 1 but we only have 1 instance ID.
		 */
		long m_numInstances;	
		long m_instanceID;
		char* m_block;
		
	private:
	
		/**
		 * This is used only inside the restoreInstance() method.
		 */
		Instance();
	};
	
public:
	/**
	 * This allows us to keep track of the next instance identifer for each
	 * type of instance we have.  The first element tells us the instance
	 * type, and the second represents the next instance number for that type.
	 */
	typedef std::map<TrackedType, long> InstanceIDs;

	/**
	 * An instance key uniquely identifies an Instance object.  It is composed
	 * of the type of the instance and the instance ID.
	 */
	typedef std::pair<TrackedType, long> InstanceKey;
	
	/**
	 * The RestoredInstanceMap keeps track of pointers to instances during
	 * the restore.  This keeps us from attempting to allocate instances multiple
	 * times during the restore.
	 */
	typedef std::map<InstanceKey, InstancePtr> RestoredInstanceMap;

	/**
	 * This function is used during restore to rebuild the IDMap.  Given a 
	 * type and an instance ID it updates the IDMap.  Note that the IDs in this
	 * map represent the next available ID that can be used for a given type.
	 * Therefore, when we update the map with the specified ID, we add 1 to the
	 * ID (so the NEXT ID is stored in the map).
	 * 
	 * @param type The type identifier
	 * @param instanceID ID of an instance object that was restored.
	 */
	static void updateIDMap(TrackedType type, long instanceID) {
		long nextID = instanceID+1;
		InstanceIDs::iterator iter = m_instanceIDs.find(type);
		if (iter == m_instanceIDs.end()) {
			m_instanceIDs[type] = nextID;
		} else {
			// Keep track of the largest ID for this type
			if (nextID > iter->second) {
				iter->second = nextID;
			}
		}
	}
	
	/**
	 * This maps the pointer to a block of memory to the Instance that holds the
	 * block.
	 */
	typedef std::map<char*, InstancePtr> InstanceContainer;

	virtual ~InstanceTracker();

	/**
	 * Create a instance and insert it into the InstanceContainer.
	 *
	 * @param ts The type of this instance
	 * @param pDB The database to allocate the instance in.
	 * @param segment The segment to allocate the instance in.
	 * @param numToAllocate The number of occurances of this type of instance to allocate.  
	 */
	static void* allocate(mc_dbms_typespec* ts, mc_dbms_database* pDB = 0, mc_dbms_segment* segment = 0, dbms_int32 numToAllocate = 1);
	
	/**
	 * Remove an instance from the InstanceContainer.
	 *
	 * @param ptr Pointer to the instance to be removed.
	 */
	static void destroy(void* ptr);
	
	/**
	 * This generates a report on the instances contained in this tracker.  There
	 * will be 2 files created by this routine in the current working directory.  
	 * the file names are: gen_stats_persistent.txt and gen_stats_transient.txt.  
	 * If files of this name already exist on disk they will be deleted.
	 *
	 * @param cleanShutdown This is true if we are about to commit the data to
	 *                      the persistent store (there were no errors).  It is
	 *                      false if we are not going to commit the data because
	 *                      an error was encountered.
	 *
	 * @return A reference to a stringstream object containing the report.
	 */
	static void report(bool cleanShutdown = true);

	/**
	 * Look through the instances and find one that the given pointer is contained
	 * in.  
	 * 
	 * @param ptr We are trying to find the Instance object that this parameter
	 *            is a part of.  
	 * @param ts The type of the item we are looking for (this allows us to 
	 *           find the object quicker.
	 * @param offset The offset of the given pointer from the beginning of the 
	 *               class.  This value is obtained using the offsetof() method
	 *               from stddef.h.  A value of -1 is supplied if no offset is
	 *               available.  When this happens, the search is linear within
	 *               the given types instance map.
	 * @return A pointer to the object that the given ptr is a part of.
	 */		 
	static void* findInstance(void* ptr, int offset);
	
	/**
	 * Find the Instance object as specified by the given pointer.  Return
	 * a pointer to the Instance object that hold the given pointer.
	 * 
	 * @param ptr We are trying to find the Instance object that this parameter
	 *            is a part of.  
	 * @return A pointer to the instance that the given ptr is contained in.
	 */	
	static InstancePtr findInstance(char* ptr);
	
	/**
	 * This routine will create an Instance, and if it's marked as persistent, it will put it
	 * in our instance container.  
	 *
	 * return A pointer to the block of memory that was allocated inside the instance.
	 */
	static InstancePtr createInstance(TrackedType typeID, int typeSize, int numToAllocate, bool isPersistent, long instanceNumber, char* objPtr = 0);

	virtual long persist();
	static void create();

	/**
	 * See if the specified instance has been restored yet or not.  If it has
	 * then return its pointer, if it hasn't, return a null pointer.  This
	 * function will thrown an exception if element if found in the map but it
	 * has a null pointer.  If this occurs it indicates a problem with 
	 * recursion in the Instance::create() method.
	 *
	 * @param typeID Type of the instance
	 * @param instanceID Identifier of the instance.
	 */
	static InstancePtr findRestoredInstance(TrackedType typeID, long instanceID) {
		InstancePtr result;
		RestoredInstanceMap::iterator iter = RestoredInstances.find( std::make_pair(typeID, instanceID) );
		if ( iter !=  RestoredInstances.end() ) {
			result = iter->second;
			if ( !result.get() ) {
				std::ostringstream msg;
				msg << "An Instance object was requested before it was fully instantiated by restore. " 
					<< "Type:" << typeID << " InstanceID: " << instanceID;
				throw std::runtime_error( msg.str() );
			}
		}
		return result;
	}
	
	/**
	 * This adds an element to the Restored Instance Map (RestoredInstances) if one didn't exist for the given key, 
	 * and updates the map if one did exist.
	 */
	static void addRestoredInstance(TrackedType type, long instanceID, InstancePtr instPtr = InstancePtr()) {
		InstanceKey instKey(type, instanceID);
		RestoredInstances[instKey] = instPtr;
	}

private:

	/**
	 * This constructor is used only for persistence.
	 */
	InstanceTracker() { }
	
	/**
	 * This returns a count of the number of instances being tracked.  If a
	 * typespec is specifed then the count for that type is returned, otherwise
	 * this function returns the count for of types.
	 */
	static int instanceCount(mc_dbms_typespec* ts = 0);

	/**
	 * Remove all data.  This function is used only by our unit tests.
	 */
	static void purge();

	/**
	 * This is a multi-map key by instance type, where all instance data
	 * is held.
	 */
	static InstanceContainer m_instances;
	
	/**
	 * This is a map key-ed by instance type where the next instance ID for 
	 * the specified type is kept.
	 */
	static InstanceIDs m_instanceIDs;
	
	/**
	 * A map, by InstanceKey, of instance pointers.  This is populated during
	 * a restore.
	 */
	static RestoredInstanceMap RestoredInstances;
};

/**
 * Placement new operator.
 * @see InstanceTracker::allocate()
 */
static void * operator new ( size_t params, mc_dbms_database* db, mc_dbms_typespec* ts)
{
    return InstanceTracker::allocate(ts, db);
}

/**
 * Placement new operator.
 * @see InstanceTracker::allocate()
 */
static void * operator new ( size_t params, mc_dbms_segment* seg, mc_dbms_typespec* ts)
{
    return InstanceTracker::allocate(ts, 0, seg);
}

/**
 * Placement new operator.
 * @see InstanceTracker::allocate()
 */
static void * operator new( size_t params, mc_dbms_database* db, mc_dbms_typespec* ts, dbms_int32 sz)
{
    return InstanceTracker::allocate(ts, db, 0, sz);
}

/**
 * Placement new operator.
 * @see InstanceTracker::allocate()
 */
static void * operator new ( size_t params, mc_dbms_segment* seg, mc_dbms_typespec* ts,dbms_int32 sz)
{
	return InstanceTracker::allocate(ts, 0, seg, sz);
}

/**
 * Placement delete operator.
 * This overload is here only to appease the compiler (so there is a matching
 * delete for every placemnet-new).  The 
 * void operator delete(void *addr, char* dummy)
 * is the one that should be used.  It is easier to call and does the same 
 * thing.
 * @see InstanceTracker::destroy(char * addr)
 */
static inline void operator delete( void * addr, mc_dbms_database* db, mc_dbms_typespec* ts) 
{
	InstanceTracker::destroy(addr);
}

/**
 * Placement delete operator.
 * This overload is here only to appease the compiler (so there is a matching
 * delete for every placemnet-new).  The 
 * void operator delete(void *addr, char* dummy)
 * is the one that should be used.  It is easier to call and does the same 
 * thing.
 * @see InstanceTracker::destroy(char * addr)
 */
static inline void operator delete( void * addr, mc_dbms_segment* seg, mc_dbms_typespec* ts) 
{
	InstanceTracker::destroy(addr);
}

/**
 * Placement delete operator.
 * This overload is here only to appease the compiler (so there is a matching
 * delete for every placemnet-new).  The 
 * void operator delete(void *addr, char* dummy)
 * is the one that should be used.  It is easier to call and does the same 
 * thing.
 * @see InstanceTracker::destroy(char * addr)
 */
static inline void operator delete( void * addr,mc_dbms_database* db, mc_dbms_typespec* ts,dbms_int32 sz)
{
	InstanceTracker::destroy(addr);
}

/**
 * Placement delete operator.
 * This overload is here only to appease the compiler (so there is a matching
 * delete for every placemnet-new).  The 
 * void operator delete(void *addr, char* dummy)
 * is the one that should be used.  It is easier to call and does the same 
 * thing.
 * @see InstanceTracker::destroy(char * addr)
 */
static inline void operator delete( void * addr, mc_dbms_segment* seg, mc_dbms_typespec* ts,dbms_int32 sz) 
{
	InstanceTracker::destroy(addr);
}

/**
* Placement delete operator.
* @see InstanceTracker::destroy()
*/
static inline void operator delete( void * addr, char *dummy) 
{
	InstanceTracker::destroy(addr);
}

#endif // _included_class_instance_tracker_

/*========================================================================
 *
 * File:      $RCSfile: collection.h,v $
 * Version:   $Revision: 1.13 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_collection_
#define _included_class_collection_ 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/SerializableObject.h>
#include <mc_dbms/typespec.h>
#include <deque>
#include <map>

class mc_dbms_cursor;
class mc_dbms_typespec;
template <class E>  class mc_dbms_Set;
template <class E>  class mc_dbms_Bag;
template <class E>  class mc_dbms_List;
template <class E>  class mc_dbms_Array;
template <class E>  class mc_dbms_Cursor;
template <class E>  class mc_dbms_Collection;

class mc_dbms_collection : public SerializableObject
{
public:

	typedef std::deque<void*> CollectionType;
	
	virtual ~mc_dbms_collection();

	/**
	 * Remove all elements from the collection.
	 */
	void clear();

	/**
	 * Return the first element of the collection or null if there are
	 * no elements. 
	 */
	void* retrieve_first() const;

	/**
	 * Return the first element of the collection or null if there are
	 * no elements. 
	 */
	void* retrieve_first();

	/**
	 * Insert the specified element into this collection before the specified
	 * offset.
	 */
	void insert_before(void* p, dbms_unsigned_int32 position);

	/**
	 * Initially, this function was implemented to return the number of unique 
	 * elements in this collection.  It was determined that this is NOT what was
	 * required in the generator.  The generator simply wants to know the 
	 * collection size.  When project Cayetano (bz i1110) was started there was
	 * no size() method in this interface.  This function now simply returns
	 * the size of the collection without regard for duplicate elements.  This
	 * was done as a performance optimization to v1.1.8 of gen_erate.exe.
	 *
	 * @return The number of elements in this collection
	 */
	int cardinality() const { return size(); }

	/**
	 * Return the first element of the collection or null if there are
	 * no elements. 
	 */
	void* pick() const;

	/**
	 * Insert the specified element into this collection.
	 */
	void insert( void* p ) {
		m_collection.push_back((void*)p);
	}

	/**
	 * Insert the specified element at the end of this collection.
	 */
	void insert_last( void * p );

	/**
	 * Retrieve the element at the specified position in the collection.  If
	 * there is no element at that position a null pointer is returned.
	 */
	void* retrieve(dbms_unsigned_int32 i) const;

	/**
	 * Returns number of elements in this collection
	 */
	operator dbms_int32() { return m_collection.size(); }

	/**
	 * Remove the specified pointer from the collection.  If there are multiple
	 * copies only the first one encounted is removed. 
	 *
	 * @return Returns non-zero if an element was removed, and 0 if an element
	 *         was not removed.
	 */
	dbms_int32 remove(void* p);

	/**
	 * Returns the element at the specified position and replaces that 
	 * element with the specified void*.  If he specified position is
	 * out of range, an std::runtime_error() exception is thrown.
	 *
	 * @returns The element at the specified position before replacement takes
	 *          place. 
	 */
	void* replace_at(void* p, dbms_unsigned_int32 position);

public:

	/**
	 * The specified collection is considered equal to this one if the 
	 * collections have the same cardinality, and
	 * count(element)==s.count(element).
	 *
	 * @param s The collection we are comparing to.
	 * @return This operator returns 1 if the collections are equal and 0 if 
	 *         they are not equal.
	 */
	dbms_int32 operator ==(const mc_dbms_collection& s) const;

	/**
	 * See if all elements in this collection have the same value as the 
	 * specified "void*".
	 *
	 * @param s The element to compare the elements of the collection to.
	 * @return 1 if the collection contains the specified element and
	 * nothing else, otherwise return 0.
	 */
	dbms_int32 operator ==(const void* e) const;

	/**
	 * This is a union operation.  It will insert the elements contained in 
	 * given collection into this collection and return a reference to the
	 * modified collection.
	 *
	 * @param s Collection to perform a union with
	 * @return The union of the current collection and the given collection
	 */
	mc_dbms_collection& operator |=(const mc_dbms_collection& s);

	/**
	 * This is a union operation.  It will insert the given into this collection
	 * and return a reference to the modified collection.
	 *
	 * @param e Element to perform a union with
	 * @return The union of the current collection and the given element
	 */
	mc_dbms_collection& operator |=(const void* e);

	/**
	 * This is an intersection operation.  For each element in this collection, 
	 * this operation will decrease the count of the element to the minimum of 
	 * the counts in the source and target (this) collections. 
	 *
	 * @param The collection to perform the intersetion operation with.
	 * @return A reference to this collection after the operation is performed.
	 */
	mc_dbms_collection& operator &=(const mc_dbms_collection& s);

	/**
	 * This is an intersection operation.  If the specified element is present 
	 * in this collection the collection will be modified to contain only the 
	 * element e, otherwise the collection will be cleared.  
	 *
	 * @param The element to perform the intersetion operation with.
	 * @return A reference to this collection after the operation is performed.
	 */
	mc_dbms_collection& operator &=(const void* e);

	/**
	 * For each element in the specified collection (s), remove s.count(e) 
	 * occurrences of the element from the target collection (this). 
	 *
	 * @param The source collection for the difference operation.
	 * @return A reference to this collection after the operation is performed.
	 */
	mc_dbms_collection& operator -=(const mc_dbms_collection& s);

	/**
	 * Remove one occurance of the specified element from this collection.
	 *
	 * @param The element to remove.
	 * @return A reference to this collection after the operation is performed.
	 */
	mc_dbms_collection& operator -=(const void* e);
		
public:    
	
	/**
	 * Returns true if the collection is empty and false if it is not empty.
	 */
	bool empty() const { return m_collection.empty(); }

	/**
	 * Return the number of elements in this collection.
	 *
	 * @return The number of elements in this collection
	 */
	int size() const { return m_collection.size(); }

	virtual long persist();
	
	static mc_dbms_collection* create();
	
	/**
	 * All embedded collection inherit (indirectly) from class SerializeableObject.
	 * We take advantage of then to perform serialization.  Given a pointer
	 * to an object that may contain embedded collections, and the type of 
	 * object that the pointers points to, we determine if this type has embedded
	 * collection(s).  If it does, for each of the embedded collections we use the
	 * offset of that embedded collection into the given object pointer to find
	 * the embedded collection.  We then cast that pointer to a "SerializeableObject*",
	 * and call the perist method.  This is repeated for each embedded collection
	 * in the object.
	 *
	 * @param objectPtr Pointer to the object that may have embedded collections.
	 * @param typeID The type identifier(mc_dbms_typespec) of the given pointer.
 	 */
	static long persistEmbeddedCollections(char* objectPtr, TrackedType typeID);

	void restoreEmbeddedCollections(char* objectPtr, TrackedType typeID);
	
	/** 
	 * This routine will create all the embedded collections in the specified object.  It
	 * does thi by iterating over these collections and calling 
	 * restoreOneEmbeddedCollection().
	 *
	 * @see restoreOneEmbeddedCollection()
	 * @param objectPtr Pointer to the object that may have embedded collections.
	 * @param typeID The type identifier(mc_dbms_typespec) of the given pointer.
	 * @param objectHasValidCollections This is a flag that tells us if the embedded collections in the given
	 *        object al valid.  If they are not, then we will instantiate new collection objects, if they are
	 *        valid then we'll use the ones that are there.
	 */
	static void createEmbeddedCollections(char* objectPtr, TrackedType typeID, bool objectHasValidCollections = false);
	
	/**
	 * This routine will create a single embedded collection.
	 * There are several embedded collection types, but from the pointer of 
	 * view of the restore process, there are only 2.  In the first type, the
	 * object that holds the collection is on the "1-side" of a relationship.  
	 * For example, OneToOne, and OneToMany.  To restore this type of collection,
	 * the "1" element (which is an embedded pointer) must be restored.  We
	 * take advantage of class SerializeablePointer to perform the restore.
	 * <br>
	 * The second type of collection is where the object that holds the collection
	 * is on the "Many"-side of a relationship.  For example, ManyToOne, and ManytoMany.
	 * These collection inherit from mc_dbms_collection.  So, to restore
	 * them, we instantiate a new mc_dbms_collection object (and restore
	 * that collection) and we then copy the pointer to that collection into
	 * the ManyToOne/ManyToMany object (the virtual function pointer is the 
	 * first 4 bytes).
	 * 
	 * @param embeddedCollType The type of the embedded collection we are being asked to restore.
	 * @param objectPtr A pointer to the location of the embedded collection.
	 *        
	 */
	static void createOneEmbeddedCollection(mc_dbms_typespec::EmbeddedCollectionType embeddedCollType, char* embeddedCollectionPtr);

	virtual void restore();

protected:
	 CollectionType m_collection;

	 static mc_dbms_typespec* get_mc_dbms_typespec();
	 static mc_dbms_typespec* get_array_typespec();
	 static mc_dbms_typespec* get_bag_typespec();
	 static mc_dbms_typespec* get_list_typespec();
	 static mc_dbms_typespec* get_set_typespec();
	 static mc_dbms_typespec* get_dict_typespec();

private:
	/**
	 * Determine the number of elements in the collection with the specified
	 * value.
	 *
	 * @return The number of occurances of the specified "void*" in this collection.
	 */
	dbms_int32 count(const void* e) const;

	static mc_dbms_typespec m_typespec;	
	static mc_dbms_typespec m_array_typespec;
	static mc_dbms_typespec m_bag_typespec;
	static mc_dbms_typespec m_list_typespec;
	static mc_dbms_typespec m_set_typespec;
	static mc_dbms_typespec m_dict_typespec;
};

template <class E>
class mc_dbms_Collection : public mc_dbms_collection 
{

protected:
  	/** 
  	 * Special constructor called by the derived class so a default 
  	 * mc_dbms_set does not get generated.
  	 */
  	mc_dbms_Collection<E>(char override) { }

public:
				  
	mc_dbms_Collection(dbms_unsigned_int32 sz = 0) { }
	
	virtual ~mc_dbms_Collection(){ }
	
	E pick() const { return (E)mc_dbms_collection::pick(); }
	
	E retrieve(dbms_unsigned_int32 i) const
	{
		return (E)mc_dbms_collection::retrieve(i);
	}
	
	void insert(E p)
	{
		mc_dbms_collection::insert((void*)p); 
	}
	
	dbms_int32 remove(E p)
	{
		return mc_dbms_collection::remove((void*)p);
	}
	
	void insert_last(E p)
	{
		mc_dbms_collection::insert_last((void*)p);
	}
	
	void insert_before(const E p, dbms_unsigned_int32 position)
	{
		mc_dbms_collection::insert_before((void*)p, position);
	}
	
	E replace_at(const E p, dbms_unsigned_int32 position)
	{
		return (E)mc_dbms_collection::replace_at((void*)p, position);
	}
	


public:
  virtual dbms_int32 operator ==(const mc_dbms_Collection<E>& s) const {
  		return mc_dbms_collection::operator ==(s);
  }
  
  virtual dbms_int32 operator ==(const E e) const {
  		return mc_dbms_collection::operator ==((void*)e);
  }
  
  virtual mc_dbms_Collection<E>& operator |=(const mc_dbms_Collection<E>& s) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator |=(s);
  }
  
  virtual mc_dbms_Collection<E>& operator |=(const E e) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator |=((void*)e);
  }
  
  virtual mc_dbms_Collection<E>& operator &=(const mc_dbms_Collection<E>& s) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator &=(s);
  }
  
  virtual mc_dbms_Collection<E>& operator &=(const E e) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator &=((void*)e);
  }
  
  virtual mc_dbms_Collection<E>& operator -=(const mc_dbms_Collection<E>& s) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator -=(s);
  }
  
  virtual mc_dbms_Collection<E>& operator -=(const E e) {
	  	return (mc_dbms_Collection<E>&)mc_dbms_collection::operator -=((void*)e);
  }
  
  /* Cast operators */
  virtual operator const mc_dbms_List<E> &() const {
    return (mc_dbms_List<E> &)*this;
  }
  
  virtual operator mc_dbms_List<E> &() {
    return (mc_dbms_List<E> &)*this;
  }
  
  virtual operator const mc_dbms_Set<E> &() const {
    return (mc_dbms_Set<E> &)*this;
  }
  
  virtual operator mc_dbms_Set<E> &() {
    return (mc_dbms_Set<E> &)*this;
  }
  
  virtual operator const mc_dbms_Bag<E> &() const {
    return (mc_dbms_Bag<E> &)*this;
  }
  
  virtual operator mc_dbms_Bag<E> &() {
    return (mc_dbms_Bag<E> &)*this;
  }
  
  virtual operator const mc_dbms_Array<E> &() const {
    return (mc_dbms_Array<E> &)*this;
  }
  
  virtual operator mc_dbms_Array<E> &() {
    return (mc_dbms_Array<E> &)*this;
  }  

public:
  	static mc_dbms_typespec* get_mc_dbms_typespec() { return mc_dbms_collection::get_mc_dbms_typespec(); }
  
  	bool empty() const { return mc_dbms_collection::empty(); }

  	int size() const { return mc_dbms_collection::size(); }

};

#endif /* _included_class_collection_ */

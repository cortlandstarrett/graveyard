/*========================================================================
 *
 * File:      $RCSfile: typespec.h,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_class_typespec_
#define _included_class_typespec_ 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#include <mc_dbms/mc_dbms_types.h>
#include <mc_dbms/SerializableObject.h>
#include <mc_dbms/tracked_types.h>
#include <map>
#include <set>

class mc_dbms_typespec : public SerializableObject
{
public:
	enum EmbeddedCollectionType { OneToOne = 0, OneToMany, ManyToOne,  ManyToMany};

    /**
     * This is a constructor that takes the name of the type being created. 
     * 
     * @param typespec The name of the type being created.
     * @param size The size of this type (in bytes).
     */
    mc_dbms_typespec(const char* typespec, long size);
    
    /**   
     * This is a copy constructor for this object.
     * 
     * @param mc_dbms_typespec_arg The object to copy.
     */
    mc_dbms_typespec(const mc_dbms_typespec& mc_dbms_typespec_arg);
        
    virtual ~mc_dbms_typespec();

    /**
     * This is a copy assignment operator for this object.
     *
     * @param mc_dbms_typespec_argc The source typespec to copy from.
     */      
    void operator=(const mc_dbms_typespec& mc_dbms_typespec_arg);
    
    /**  
     * This compares two typespecs and returns true if they represent the same type.
     *
     * @param mc_dbms_typespec_arg The object to compare to.
     * @return This function return true if the objects are equal false if they are not. 
     */
    dbms_boolean operator==(const mc_dbms_typespec& mc_dbms_typespec_arg) const;
    
    /** 
     * This compares the typespec to a name and returns true if the typespec's name
     * matches.
     *
     * @param name_arg The name to compare to.
     * @return This function return true if the objects are equal false if they are not.
     */
    dbms_boolean name_is(const char* name_arg) const { return m_typename == name_arg; }

	/**
	 * This returns the size of the type represented by this typespec.
	 */
	long size() { return m_size; }
	
	/**
	 * Given the string representation of a type, this function return the
	 * type's numeric identifier.  
	 *
	 * @param type The string representation of the type
	 * @return The type's numeric identifier.
	 */
	TrackedType get_type_id() { 
		if (m_typeID == tt_UnitializedTypeID) {
			m_typeID = lookupTypeID(m_typename);
		}
		return m_typeID;
	}
	
    /**  
     * This accessor returns the name of the type this object represents.
     *
     * @return A pointer to the name type.
     */      
    const char* get_name() const { return m_typename.c_str(); }
    
    /**
     * This returns the name associated with a type id.
     * @param type_id The type id to look up
     * @returns The character string represented by this type id.
     */
    static const char* get_name(TrackedType type_id);
    
    /**
     * @return A pointer to the mc_dbms_typespec that represents the char type. 
     */
    static mc_dbms_typespec* get_char() { return &Char_Type; };
    
    /**  
     * @return A pointer to the mc_dbms_typespec that represents the unsigned char type. 
     */
    static mc_dbms_typespec* get_unsigned_char() { return &UChar_Type; }
    
    /**  
     * @return A pointer to the mc_dbms_typespec that represents the unsigned short type. 
     */
    static mc_dbms_typespec* get_unsigned_short() { return &UShort_Type; }
    
    /**  
     * @return A pointer to the mc_dbms_typespec that represents the unsigned long type. 
     */
    static mc_dbms_typespec* get_unsigned_long() { return &ULong_Type; }

	const static long UnitializedTypeID;
	
	/**
	 * Add an embedded collection for this typespec.
	 */
	static void addEmbeddedCollection(TrackedType typeID, int offset, EmbeddedCollectionType collType);

	/**
	 * This contains the offsets of embedded collections and the type of the
	 * collection at that offset.  No duplicate offsets are allowed for a given 
	 * type. It doesn't make sense for the same offset to exit more then
	 * one type in this collection).
	 */
	typedef std::map<int, EmbeddedCollectionType> EmbeddedCollectionData;

	/**
	 * This maps a typespec identifier to the offsets of the embedded collections 
	 * inside that type.  This helps us find these embedded collections for  
	 * persistence and restoration.
	 */
	 typedef std::map<TrackedType, EmbeddedCollectionData > EmbeddedCollectionMap;

	/**
	 * This contains information about offsets of embedded collections with all
	 * known types.
	 */
	static EmbeddedCollectionMap EmbeddedCollections;
	
	/**
	 * This tells us if the specified type inherits from class SerializeableObject
	 */
	static bool isSerializableType(TrackedType type);

	/**
	 * This returns true if the given value specifies one of the mc_dbms_collection
	 * types.
	 */	
	static bool isCollectionType(TrackedType type);

	/**
	 * This method is used to serialize the infomation that this class tracks
	 * about location and type of embedded collections.
	 */
	static long serialize();

	virtual long persist();

	static void restore();

private:

	/**
	 * Find the numeric type id for the given type name string.
	 *
	 * @param type The string representation of the type
	 * @return The type's numeric identifier.
	 */
	TrackedType lookupTypeID(const std::string& type);

	/**
	 * This function populates the type-map the first time it is accessed.
	 */
	static void mc_dbms_typespec::loadTypeMap();

	/**
	 * This maps the type name to a numeric identifier associated with the
	 * type.  The numeric identifiers start with 1 and increase from there.
	 * Values of less-then or equal 0 are invalid IDs.
	 */
	typedef std::map<std::string, TrackedType >	NameMap;
	static  NameMap Types;
	static bool MapIsLoaded;

	std::string m_typename;
	TrackedType m_typeID;
	long m_size;

	// These four are types that are only allocated once.
	static mc_dbms_typespec Char_Type;
	static mc_dbms_typespec UChar_Type;
	static mc_dbms_typespec UShort_Type;
	static mc_dbms_typespec ULong_Type;
};

#endif /* _included_class_typespec_ */

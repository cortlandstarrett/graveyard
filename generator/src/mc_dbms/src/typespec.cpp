/*========================================================================
 *
 * File:      $RCSfile: typespec.cpp,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/typespec.h>
#include <iostream>

mc_dbms_typespec mc_dbms_typespec::Char_Type( "char", sizeof(char) );
mc_dbms_typespec mc_dbms_typespec::UChar_Type( "uchar", sizeof(unsigned char) );
mc_dbms_typespec mc_dbms_typespec::UShort_Type( "ushort", sizeof(unsigned short) );
mc_dbms_typespec mc_dbms_typespec::ULong_Type( "ulong", sizeof(unsigned long) );
mc_dbms_typespec::NameMap mc_dbms_typespec::Types;
bool mc_dbms_typespec::MapIsLoaded = false;

mc_dbms_typespec::EmbeddedCollectionMap mc_dbms_typespec::EmbeddedCollections;

mc_dbms_typespec::mc_dbms_typespec(const char* typespec, long size) :
	m_typename(typespec),
	m_size(size),
	m_typeID(tt_UnitializedTypeID)
{
}

mc_dbms_typespec::mc_dbms_typespec(const mc_dbms_typespec& that)
{
	// We implement this using the assignment operator (so we only have to 
	// maintain the code in one place).
	*this = that;
}

mc_dbms_typespec::~mc_dbms_typespec()
{
}

TrackedType mc_dbms_typespec::lookupTypeID(const std::string& type) {
	if (!MapIsLoaded) {
		mc_dbms_typespec::loadTypeMap();
	}
		
	TrackedType id = tt_UnitializedTypeID;
	mc_dbms_typespec::NameMap::iterator iter = Types.find(type);
	if (iter != Types.end()) {
		id = iter->second;
	}
	return id;	
}

const char* mc_dbms_typespec::get_name(TrackedType type_id)
{
	const char* name = "not_found";
	mc_dbms_typespec::NameMap::iterator iter = Types.begin();
	bool found = false;
	for (; !found && iter != Types.end(); ++iter) {
		if (iter->second == type_id) {
			name = iter->first.c_str();
			found = true;
		}
	}
	return name;
}

void mc_dbms_typespec::loadTypeMap()
{
	// We'll start with "1" making 0 (or smaller) an invalid value.  One reason 
	// for this is that we want to be able to tell the difference between 
	// something that has not been initialized vs something that may be a real 
	// type identifier.
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("char"), 							tt_char) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("uchar"),							tt_uchar) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("ushort"), 							tt_ushort) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("ulong"), 							tt_ulong) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_collection"), 				tt_mc_dbms_collection) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_Array"), 					tt_mc_dbms_Array) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_Bag"), 					tt_mc_dbms_Bag) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_List"), 					tt_mc_dbms_List) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_Set"), 					tt_mc_dbms_Set) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_Dictionary"), 				tt_mc_dbms_Dictionary) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("mc_dbms_cursor"), 					tt_mc_dbms_cursor) );

	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_frag_ref_var"), 					tt_I_frag_ref_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_timer_inst_ref_var"), 			tt_I_timer_inst_ref_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_mapping_inst_ref_var"), 			tt_I_mapping_inst_ref_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_date_var"), 						tt_I_date_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_timestamp_var"), 				tt_I_timestamp_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_mapping_inst_var"), 				tt_I_mapping_inst_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_event_inst_var"), 				tt_I_event_inst_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_object_inst_ref_var"), 			tt_I_object_inst_ref_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_object_inst_ref_set_var"), 		tt_I_object_inst_ref_set_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_current_state_var"), 			tt_I_current_state_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_unique_id_var"), 				tt_I_unique_id_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_string_var"), 					tt_I_string_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_real_var"), 						tt_I_real_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_integer_var"), 					tt_I_integer_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_boolean_var"), 					tt_I_boolean_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_enumerator_var"), 				tt_I_enumerator_var) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_void_var"), 						tt_I_void_var) );
	
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Chain_Rel_Obj_Pair"), 			tt_I_Chain_Rel_Obj_Pair) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Related_Object_Pair"), 			tt_I_Related_Object_Pair) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Attribute_Instance"), 			tt_I_Attribute_Instance) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Object_Instance"), 				tt_I_Object_Instance) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_ID_Attribute_Reference"),		tt_I_ID_Attribute_Reference) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_ID_REF_Rel_Obj_Pair"), 			tt_I_ID_REF_Rel_Obj_Pair) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Relationship"), 					tt_I_Relationship) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Object"), 						tt_I_Object) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Attribute"), 					tt_I_Attribute) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_SM_Evt_Inst"), 					tt_I_SM_Evt_Inst) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Clock"), 						tt_I_Clock) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_SM_Evt_Supp_DI_Inst"), 			tt_I_SM_Evt_Supp_DI_Inst) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_SM_Evt"), 						tt_I_SM_Evt) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_Related_Object_Instance_Pair"),	tt_I_Related_Object_Instance_Pair) );
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("Id_assigner"),						tt_Id_assigner) );	
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("String"),							tt_String) );	
	mc_dbms_typespec::Types.insert( std::make_pair( std::string("I_SM_Evt_Supp_DI"),				tt_I_SM_Evt_Supp_DI) );	
	
	mc_dbms_typespec::MapIsLoaded = true;
}

bool mc_dbms_typespec::isCollectionType(TrackedType type)
{
	bool isCollection = false;
	
	switch (type) {
	case tt_mc_dbms_collection:
	case tt_mc_dbms_Array:
	case tt_mc_dbms_Bag:
	case tt_mc_dbms_List:
	case tt_mc_dbms_Set:
	case tt_mc_dbms_Dictionary:     
		isCollection = true;
		break;
	default:
		isCollection = false;
	}
	return isCollection;
}

bool mc_dbms_typespec::isSerializableType(TrackedType type)
{
	bool isExternalSerializableType = false;

	switch (type) {
	case tt_I_frag_ref_var:
	case tt_I_timer_inst_ref_var:
	case tt_I_mapping_inst_ref_var:
	case tt_I_date_var:
	case tt_I_timestamp_var:
	case tt_I_mapping_inst_var:
	case tt_I_event_inst_var:
	case tt_I_object_inst_ref_var:
	case tt_I_object_inst_ref_set_var:
	case tt_I_current_state_var:
	case tt_I_unique_id_var:
	case tt_I_string_var:
	case tt_I_real_var:
	case tt_I_integer_var:
	case tt_I_boolean_var:
	case tt_I_enumerator_var:
	case tt_I_void_var:
	case tt_I_Attribute_Instance:
	case tt_I_ID_REF_Rel_Obj_Pair:
	case tt_I_Chain_Rel_Obj_Pair:	
	case tt_I_Relationship:
	case tt_I_Object:
	case tt_I_Attribute:
	case tt_I_Related_Object_Instance_Pair:
		isExternalSerializableType = true;
		break;
	}

	return (isCollectionType(type) || isExternalSerializableType );
}


void mc_dbms_typespec::operator=(const mc_dbms_typespec& that)
{
	m_typename = that.m_typename;
	m_size = that.m_size;
	m_typeID = that.m_typeID;
}


dbms_boolean mc_dbms_typespec::operator==(const mc_dbms_typespec& that) const
{
	return (m_typename == that.m_typename &&
			m_size == that.m_size);
}

void mc_dbms_typespec::addEmbeddedCollection(TrackedType typeID, int offset, EmbeddedCollectionType collType) 
{
	EmbeddedCollectionMap::iterator iter = EmbeddedCollections.find(typeID);
	if (iter != EmbeddedCollections.end()) {
		if (iter->second.find(offset) == iter->second.end()) {
			iter->second.insert( std::make_pair(offset, collType) );
		}
	} else {
		EmbeddedCollectionData collData;
		collData.insert( std::make_pair(offset, collType) );
		EmbeddedCollections.insert( std::make_pair(typeID, collData) );
	}
	
	// In gen_db there is inheritance used in 1 place... For this case, we need
	// to make sure to update offsets for the derived class so that when embedded
	// classes are persisted and restored, the derived class will contian the information
	// for the embedded classes that are in the parent.
	if (typeID == tt_I_Related_Object_Pair) {
		addEmbeddedCollection(tt_I_ID_REF_Rel_Obj_Pair, offset, collType);
		addEmbeddedCollection(tt_I_Chain_Rel_Obj_Pair, offset, collType);
	}
}

long mc_dbms_typespec::serialize() 
{
	// Number of types in the collection
	long bytesWritten = writeLong(EmbeddedCollections.size());
	EmbeddedCollectionMap::iterator typeIter = EmbeddedCollections.begin();		
	for (; typeIter != EmbeddedCollections.end(); ++typeIter) {
		// TypeID
		bytesWritten += writeLong( typeIter->first );
		
		// Number of embedded collections for this type
		bytesWritten += writeLong(typeIter->second.size());
		EmbeddedCollectionData::iterator collIter = typeIter->second.begin();
		for (; collIter != typeIter->second.end(); ++collIter) {
			// Offset
			bytesWritten += writeLong(collIter->first);
			// Embedded Collection Type
			bytesWritten += writeLong(collIter->second);
		}
	}
	return bytesWritten;
}

long mc_dbms_typespec::persist() 
{ 
	return mc_dbms_typespec::serialize();
}

void mc_dbms_typespec::restore() 
{
	// Number of types in the collection
	long numTypes = readLong();
	for (int i = 0; i < numTypes; ++i) {
		TrackedType typeID = (TrackedType)readLong();
		long numEmbeddedColl = readLong();
		for (int j = 0; j < numEmbeddedColl; ++j) {
			long offset = readLong();
			// Embedded Collection Type
			EmbeddedCollectionType embeddedCollType = (EmbeddedCollectionType)readLong();
			addEmbeddedCollection(typeID, offset, embeddedCollType);
		}
	}
}


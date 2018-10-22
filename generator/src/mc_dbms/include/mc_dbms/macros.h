/*========================================================================
 *
 * File:      $RCSfile: macros.h,v $
 * Version:   $Revision: 1.13 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
/**
 * This file contains macros that are used in the Generator.
 */
#ifndef _included_macros_
#define _included_macros_ 1

#include <mc_dbms/SerializablePointer.h>
#include <mc_dbms/typespec.h>
#include <mc_dbms/collection.h>
#include <mc_dbms/database.h>
#include <cstddef>

#define Concatnames(u,v,w,x,y,z)u##v##w##x##y##z
#define mc_dbms_relationship_1_1_body( basetype, member,type,inv ) \
	bool basetype::Concatnames( basetype,member,type,inv,1_,1_ )::InfoCaptured = false; \
	basetype::Concatnames( basetype,member,type,inv,1_,1_ )::Concatnames( basetype,member,type,inv,1_,1_ )() \
	{ \
		if (mc_dbms_database::serializationIsEnabled() && !InfoCaptured ) { \
			/* Find the offset of this member variable */ \
			int offset = offsetof(class basetype, member); \
			mc_dbms_typespec* ts = basetype::get_mc_dbms_typespec(); \
			mc_dbms_typespec::addEmbeddedCollection(ts->get_type_id(), offset, mc_dbms_typespec::OneToOne); \
			InfoCaptured = true; \
		} \
	}

#define mc_dbms_relationship_1_1( basetype, member,type,inv,signature ) \
public: \
friend class Concatnames( basetype,member,type,inv,1_,1_ ); \
class Concatnames( basetype,member,type,inv,1_,1_ ) : public SerializablePointer \
{ \
public: \
	Concatnames( basetype,member,type,inv,1_,1_ )(); \
	~Concatnames( basetype,member,type,inv,1_,1_ )() {} \
	type* getvalue() \
	{ \
		return (type*)getPointer(); \
	} \
	operator type* () const \
	{ \
		return (type*)getPointer(); \
	} \
	type* operator->() const \
	{ \
		return (type*)getPointer();\
	} \
	type* operator=(type* val) \
 	{ \
		setPointer(val); \
		return (type*)getPointer(); \
	} \
	\
private: \
	/* Flag to tell if we captured info for this embedded collection yet. */ \
	static bool InfoCaptured; \
}
  
#define mc_dbms_relationship_m_1_body( basetype, member,type,inv ) \
	bool basetype::Concatnames( basetype,member,type,inv,m_,1_ )::InfoCaptured = false; \
	basetype::Concatnames( basetype,member,type,inv,m_,1_ )::Concatnames( basetype,member,type,inv,m_,1_ )() \
	{ \
		if (mc_dbms_database::serializationIsEnabled() && !InfoCaptured ) { \
			/* Find the offset of this member variable */ \
			int offset = offsetof(class basetype, member); \
			mc_dbms_typespec* ts = basetype::get_mc_dbms_typespec(); \
			mc_dbms_typespec::addEmbeddedCollection(ts->get_type_id(), offset, mc_dbms_typespec::ManyToOne); \
			InfoCaptured = true; \
		} \
	}

#define mc_dbms_relationship_m_1( basetype, member,type,inv,signature ) \
public: \
friend class Concatnames( basetype,member,type,inv,m_,1_ ); \
class Concatnames( basetype,member,type,inv,m_,1_ ) : public mc_dbms_collection \
{ \
public: \
	friend class type; \
	Concatnames( basetype,member,type,inv,m_,1_ )(); \
	~Concatnames( basetype,member,type,inv,m_,1_ )() {} \
	signature const& getvalue() const \
	{ \
		return *(signature*)this; \
	} \
	signature& getvalue() \
	{ \
		return *(signature*)this; \
 	} \
	operator signature& () const \
	{ \
		return (*(signature*)(this));\
	} \
	type* retrieve( dbms_unsigned_int32 place) \
	{ \
		return (type*)(mc_dbms_collection::retrieve(place)); \
	} \
	type* retrieve_first() \
	{ \
		return (type*)(mc_dbms_collection::retrieve_first()); \
	} \
	\
private: \
	/* Flag to tell if we captured info for this embedded collection yet. */ \
	static bool InfoCaptured; \
}
  
#define mc_dbms_relationship_1_m_body( basetype, member,type,inv ) \
	bool basetype::Concatnames( basetype,member,type,inv,1_,m_ )::InfoCaptured = false; \
	basetype::Concatnames( basetype,member,type,inv,1_,m_ )::Concatnames( basetype,member,type,inv,1_,m_ )() \
	{ \
		if (mc_dbms_database::serializationIsEnabled() && !InfoCaptured ) { \
			/* Find the offset of this member variable */ \
			int offset = offsetof(class basetype, member); \
			mc_dbms_typespec* ts = basetype::get_mc_dbms_typespec(); \
			mc_dbms_typespec::addEmbeddedCollection(ts->get_type_id(), offset, mc_dbms_typespec::OneToMany); \
			InfoCaptured = true; \
		} \
	} \
	void basetype::Concatnames( basetype,member,type,inv,1_,m_ )::relate(void* val, void* caller) \
 	{ \
 		void* priorVal = getPointer(); \
		setPointer(val); \
		if ( val ) { \
			reinterpret_cast<type*>( val )->inv.insert( caller ); \
			insertCompleted(); \
		} else { \
			/* If we are removing an element from the collection by assigning */ \
			/* a value of 0, then remove the "caller" from the other-side of */ \
			/* this relationship. */ \
			if ( priorVal && insertWasPerformed() ) { \
				reinterpret_cast<type*>( priorVal )->inv.remove( caller ); \
			} \
		} \
	}

#define mc_dbms_relationship_1_m( basetype, member,type,inv,signature ) \
public: \
friend class Concatnames( basetype,member,type,inv,1_,m_ ); \
class Concatnames( basetype,member,type,inv,1_,m_ ) : public SerializablePointer \
{ \
public: \
	friend class type; \
	Concatnames( basetype,member,type,inv,1_,m_ )(); \
	~Concatnames( basetype,member,type,inv,1_,m_ )() { } \
	type* getvalue() \
	{ \
		return (type*)getPointer(); \
	} \
	operator type* () const\
	{ \
		return (type*)getPointer();\
	} \
	type* operator->() const\
	{ \
		return (type*)getPointer();\
	} \
	void relate( void* val, void* caller ); \
	type* operator=(type* val); \
	\
private: \
	/* Flag to tell if we captured info for this embedded collection yet. */ \
	static bool InfoCaptured; \
}


#define mc_dbms_relationship_m_m_body( basetype, member,type,inv ) \
	bool basetype::Concatnames( basetype,member,type,inv,m_,m_ )::InfoCaptured = false; \
	basetype::Concatnames( basetype,member,type,inv,m_,m_ )::Concatnames( basetype,member,type,inv,m_,m_ )() \
	{ \
		if (mc_dbms_database::serializationIsEnabled() && !InfoCaptured ) { \
			/* Find the offset of this member variable */ \
			int offset = offsetof(class basetype, member); \
			mc_dbms_typespec* ts = basetype::get_mc_dbms_typespec(); \
			mc_dbms_typespec::addEmbeddedCollection(ts->get_type_id(), offset, mc_dbms_typespec::ManyToMany); \
			InfoCaptured = true; \
		} \
	}

#define mc_dbms_relationship_m_m( basetype, member,type,inv,signature ) \
public: \
friend class Concatnames( basetype,member,type,inv,m_,m_ ); \
class Concatnames( basetype,member,type,inv,m_,m_ ) : public mc_dbms_collection \
{ \
public: \
	Concatnames( basetype,member,type,inv,m_,m_ )(); \
	~Concatnames( basetype,member,type,inv,m_,m_ )() {} \
 	signature& getvalue() \
	{ \
		return *(signature*)this; \
	} \
	signature const& getvalue() const \
	{ \
		return *(signature*)this; \
	} \
	operator signature& ()  const\
	{ \
		return *(signature*)this; \
	} \
	type* retrieve( dbms_unsigned_int32 place) \
	{ \
		return (type*)(mc_dbms_collection::retrieve(place)); \
	} \
	type* pick() \
	{ \
		return (type*)(mc_dbms_collection::pick()); \
	} \
	\
private: \
	/* Flag to tell if we captured info for this embedded collection yet. */ \
	static bool InfoCaptured; \
}

#endif // _included_macros_

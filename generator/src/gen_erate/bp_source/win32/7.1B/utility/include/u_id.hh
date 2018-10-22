/*========================================================================
 *
 * File:      $RCSfile: u_id.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef U_ID_HH
#define U_ID_HH


//
// CONTENTS: This file describes general-purpose ID classes that can be
// used to assign unique ids.
//
// REMARKS: Note that these classes are orthogonal to persistence/transience.
// Changes have been made on 6/28/95 for ASCII Version Management.
//


// #include <vstddef.h>
#include <stddef.h>


#include "u_typdef.hh"
#include "u_error.hh"




// Declare all classes defined in this file here so they may be referenced
// (if needed) before they are declared. This also gives the User a quick
// glance at what classes reside in this file.

class Id;
class Id_assigner;



// CLASS: Id
//
// DESCRIPTION: This class creates an Id that can be used by any type of
// data structure or code segment for assigning ids.
//
// REMARKS: Note that the extra data field for class type allows
// specialization of Id types; accordingly, this class may serve as
// a base class for more refined ids. However, for safety reasons we
// don't want to give the derived class access to the member variables
// (hence private and not protected).
//

class Id
	{
	friend Id_assigner;

	public:
		// Define any relevant public "constants" first

		static const Id Default; // used for default value in function arguments

		// the id portion is broken down as follows -
		//    upper 4 bits:  domain_id
		//    middle 9 bits: config_id
		//    lower 19 bits: value_id

		enum  { NO_ID = 0 };
		enum  { NO_CLASS_TYPE = -1 };
		enum  { MAX_NUM_VALUES = 524288 };
		enum  { MAX_NUM_CONFIGS = 512 };
		enum  { MAX_NUM_DOMAINS = 16 };

		// MANAGER functions

		// All the following Id constructors are valid:
		//	Id id1, id2( 500, MY_OWN_CLASS_TYPE, 1 );
		// 	Id id3( id2 );
		//	Id id4( 500, MY_OWN_CLASS_TYPE, 1, 0 );

		Id () { id = NO_ID; class_type = NO_CLASS_TYPE; }

		Id ( const Id & p_id ) { id = p_id.id; class_type = p_id.class_type; }

		// We must also include a constructor that breaks down the "value"
		// portion into a domain code, configuration id, and value.

		Id ( t_uint p_value_id, int p_class_type, t_uint p_config_id,
			t_uint p_domain_id = 0 )
			{
			id = NO_ID;
			set_class_type( p_class_type );
			set_value_id( p_value_id );
			set_config_id( p_config_id );
			set_domain_id( p_domain_id );
			}

		~Id () {}

		// IMPLEMENTOR functions

		Id & operator=( t_uint p_id )
			{ id = p_id; class_type = NO_CLASS_TYPE; return *this; }
		Id & operator=( const Id & p_id )
			{ id = p_id.id; class_type = p_id.class_type; return *this; }

		t_boolean operator==( const Id & p_id ) const
			{
			if ( ( id == p_id.id ) && ( class_type == p_id.class_type ) )
				return TRUE;
			else
				return FALSE;
			}

		t_boolean operator!=( const Id & p_id ) const
			{
			return( ! ( *this == p_id ) );
			}

		Id & inc_value_id()
			{
			t_uint cur_value = get_value_id();
			if ( cur_value >= MAX_NUM_VALUES )
				{
				LOG_ERROR( ( L_log_string,
					"Cannot assign new id for class_type = %d, config_id = %d, value = %d because no more Id values available!",
					get_class_type(), get_config_id(), get_value_id() ));
				}
			else
				{
				cur_value++;
				set_value_id( cur_value );
				}
			return *this;
			}

		Id & inc_config_id()
			{
			t_uint cur_config = get_config_id();
			if ( cur_config >= MAX_NUM_CONFIGS )
				{
				LOG_ERROR( ( L_log_string,
					"Cannot assign new id for class_type = %d, config_id = %d, value = %d because no more Id configs available!",
					get_class_type(), get_config_id(), get_value_id() ));
				}
			else
				{
				cur_config++;
				set_config_id( cur_config );
				}
			return *this;
			}

		// ACCESS functions.

		// the following get_entire_value() replaces the old get_value()

		t_uint get_entire_value() const { return id; }

		void set_entire_value( t_uint p_entire_value )
			{ id = p_entire_value; }


		// Following ACCESS functions are for accessing the individual
		// components of the id portion. It is IMPORTANT to note that the
		// return values will always be the entity/stand-alone value, and
		// not where this value is embedded in the id (eg - if the config
		// portion/bit-field of the id is 5, then 5 will be the return value.)

		t_uint get_domain_id() const { return( ( id >> 28 ) & 0xf ); }
		t_uint get_config_id() const { return( ( id >> 19 ) & 0x1ff ); }
		t_uint get_value_id()  const { return( id & 0x7ffff ); }

        // i2778.2.1 move begin
		void set_config_id( t_uint p_config )
			{
			id = ( ( p_config & 0x1ff ) << 19 ) | ( id & 0xf007ffff );
			}
        // i2778.2.1 move end

		// IMPORTANT: User must define the class types with caution to ensure
		// they are unique. Note they must set to an unsigned int, but we may
		// return an int when getting the value since an unassigned class type
		// equals NO_CLASS_TYPE ( -1 ).

		int get_class_type() const { return class_type; }
		void set_class_type( t_uint p_class_type ) { class_type = p_class_type;}

	private:

		// the id portion is broken down as follows -
		//    upper 4 bits:  domain_id
		//    middle 9 bits: config_id
		//    lower 19 bits: value_id

		unsigned int id;
		int class_type;	// Unset value will equal -1, but Users must set to
						// whole numbers.

		// HELPING functions

		void set_value_id( t_uint p_value )
			{
			id = ( p_value & 0x7ffff ) | ( id & 0xfff80000 );
			}

		void set_domain_id( t_uint p_domain )
			{
			id = ( ( p_domain & 0xf ) << 28 ) | ( id & 0x0fffffff );
			}
	};


//
// CLASS: Id_assigner
//
// DESCRIPTION: This class is responsible for assigning new unique Id's
// to new instances of objects that contain an Id as a data member.
//
// REMARKS: These class is needed to resolve the problem of assigning
// unique Ids. A single instance of this object should be a "conceptually
// static" data member of each object that needs an Id.
//

class Id_assigner
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Id_assigner( t_uint p_value_id, int p_class_type, t_uint p_config_id,
			t_uint p_domain_id = 0 )
			:
			next_id( p_value_id, p_class_type, p_config_id, p_domain_id )
				{}

		~Id_assigner () {}

		// IMPLEMENTOR functions

		// ACCESS functions.

		Id assign_next_id() { return next_id.inc_value_id(); }
        // i2778.1.3 deletion

		Id get_current_id()
			{ return next_id; }

		// The following get_current_assigner_entire_value() replaces the
		// old legacy get_current_assigner_value().

		t_uint get_current_assigner_entire_value()
			{ return next_id.get_entire_value(); }

		// Individual id fields

		t_uint get_current_assigner_value_id()
			{ return next_id.get_value_id(); }
		t_uint get_current_assigner_config_id()
			{ return next_id.get_config_id(); }
		t_uint get_current_assigner_domain_id()
			{ return next_id.get_domain_id(); }

		void set_current_assigner_value_id( t_uint p_value_id )
			{ next_id.set_value_id( p_value_id ); }

		void set_current_assigner_id( t_uint p_value,
					int p_class_type, t_uint p_config, t_uint p_domain = 0 )
			{ 
		  	Id id( p_value, p_class_type, p_config, p_domain ); 
		  	next_id = id; 
			}

		void set_current_assigner_entire_value( t_uint p_entire_value )
			{ next_id.set_entire_value( p_entire_value ); }

        void update_next_value ( t_uint p_value_id );   // i2778.3.1.1  added

	private:

		Id next_id;

		// HELPING functions
	};







#endif

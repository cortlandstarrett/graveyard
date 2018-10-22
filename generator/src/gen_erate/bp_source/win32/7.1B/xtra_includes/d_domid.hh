/*========================================================================
 *
 * File:      $RCSfile: d_domid.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:06 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_DOMAIN_ID_HH
#define D_DOMAIN_ID_HH

//
// FILE: D_domain_id.hh	 AUTHOR: David E. Solomon	CREATION DATE: 2/14/93
//
// CONTENTS: Classes for identifiying a Domain instance.
//
// REMARKS: These classes are intended bo be used only in the TRANSIENT
//	spectrum.
//


// Include those header files that are DIRECTLY needed by this one.


#include "memory.h"

#include <u_trace.hh>
#include <u_error.hh>

#include "u_typdef.hh"
#include "u_id.hh"

#include "d_typdef.hh"


// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Domain_id;
class Domain_reference;

// Also declare classes in other subsystem that we reference, but don't
// include header file.

class Domain;

//
// CLASS: Domain_id
//
// DESCRIPTION: Instances of this class are used to uniquely identify a
//	Domain within a given Invocation.
//
// REMARKS: It is important to note that instances of this class should
//	be transient for a given Invocation only. There is NO need for instances
//	of this class to be persistent. There also is no need for each Domain
//	instance to have an instance of this class as an embedded member since
//	a database only has one Domain instance allocated (ie - we can navigate
//	to a Domain instance in a given database simply via the mc_dbms_database
//	pointer and the DOMAIN_ROOT). As a matter-of-fact, we CAIN'T put one
// 	of these in each Domain instance because for different Invocations the
//	same Domain could have different Id's.
//

class Domain_id
	{
	public:
		// MANAGER functions

		Domain_id( t_uint p_id = Id::NO_ID )
			:
			id( p_id, DOMAIN_TYPE, 0, 0 )
				{}

		Domain_id( const Id &p_id )
			:
			id( p_id.get_value_id(), DOMAIN_TYPE, p_id.get_config_id(),
				p_id.get_domain_id() )
				{}

		~Domain_id() {}

		// IMPLEMENTOR functions

		t_boolean operator==( const Domain_id &p_domain_id ) const
			{
			if ( id == p_domain_id.id )
				return TRUE;
			else
				return FALSE;
			}

		t_boolean operator!=( const Domain_id &p_domain_id ) const
			{
			return ( ! ( *this == p_domain_id ) );
			}

		// ACCESS functions.

		Id get_domain_id() const { return id; }
		Domain *get_domain_ptr() const;
		Domain *resolve() const { return get_domain_ptr(); }
		Domain *operator->() const { return get_domain_ptr(); }
		mc_dbms_database *get_db_ptr() const;

	private:

		Id id;

		// HELPING functions.
	};


//
// CLASS: Domain_reference
//
// DESCRIPTION: Instances of this class are used to uniquely identify a
//	Domain within a given Invocation and to navigate to that Domain
//	given a Domain_id.
//
// REMARKS: It is important to note that instances of this class should
//	be transient for a given Invocation only. There is NO need for instances
//	of this class to be persistent.
//

class Domain_reference
	{
	public:
		// MANAGER functions

		Domain_reference( mc_dbms_database *p_db_ptr );

		~Domain_reference();

		// IMPLEMENTOR functions

		// ACCESS functions.

		Domain_id get_domain_id() const { return id; }
		Domain *get_domain_ptr() const;
		Domain *resolve() const { return get_domain_ptr(); }
		Domain *operator->() const { return get_domain_ptr(); }
		mc_dbms_database *get_db_ptr() const { return db_ptr; }

	private:

		static Id_assigner id_assigner;

		const Domain_id id;
		mc_dbms_database *db_ptr;

		// HELPING functions.
	};


#endif /* D_DOMAIN_ID_HH */

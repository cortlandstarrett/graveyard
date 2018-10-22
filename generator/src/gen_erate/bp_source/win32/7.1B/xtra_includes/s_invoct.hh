/*========================================================================
 *
 * File:      $RCSfile: s_invoct.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SINVOCATION_HH
#define SINVOCATION_HH

//
// FILE: Sinvocation.hh	AUTHOR: Don Cornwell    CREATION DATE: 5/27/94
//
// CONTENTS:
//
//		This file describes the C++ classes relating to a given Sim
//		invocation.
//
// REMARKS:
//
//		One transient instance of this class should be created for each
//		SIM invocation. Because we can only have one instance
//		of this class, all members will be static.
//
//		A given SIM invocation will operate upon zero, one or
//		more domains (from zero, one, or more .ooa files) and operate
//		on zero, one, or more simulations (.sim files).  Only one
//		simulation will be active at any one time.  However, a 
//		simulation can interact with all loaded domains.  This
//		allows a simulation of multiple domains.
//
//		Note that the init() function provided by this class is the
//		highest level init function for the tool invocation.
//

// Include those header files that are DIRECTLY needed by this one.
#include <s_simref.hh>
#include <u_string.hh>

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Sinvocation;

// Also declare classes in other subsystem that we reference but don't
// include the header files.


//
// CLASS: Sinvocation
//
// DESCRIPTION:
//
//		This defines the information needed for each BridgePoint Simulator
//		invocation.
//
// REMARKS:
//
//		The instances of this class will always be transient. Since
//		only one of these will ever be created, we will make all
//		functions and data static so the User will not have to keep a
//		clumsy pointer to the single Sinvocation instance.
//		As a matter of fact, we won't even provide a constructor
//		since all data is static.
//

class Sinvocation
{
	public:
		// MANAGER functions

		static void init();

		// IMPLEMENTOR functions
		static mc_dbms_database *create_database(
			const char *p_sim_db_full_pathname, 
			GS_string &p_err_msg );

		static mc_dbms_database *open_database(
			const char *p_sim_db_full_pathname, 
			GS_string &p_err_msg );

		static Sim_reference *first_sim_ref();
		static Sim_reference *next_sim_ref();
		static void done_with_sim_ref();

		static void insert_sim_ref( Sim_reference *p_sim_ref_ptr )
			{ sim_refs->insert( p_sim_ref_ptr ); }

         static void reinit();


	private:
		// Don't even allow the constructors to be invoked by User

		Sinvocation() {}
		~Sinvocation() {}
		
		// The following collection allows us to model a TRANSIENT
		// class-extent of all Simulations open for a given Sinvocation.
		// Via each Sim_reference, we can navigate to the corresponding
		// persistent I_Object instance. 
		
		static mc_dbms_List< Sim_reference * > *sim_refs;

		static mc_dbms_Cursor< Sim_reference *> *sim_refs_cursor_ptr;

};

#endif

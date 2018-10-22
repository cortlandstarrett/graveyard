/*========================================================================
 *
 * File:      $RCSfile: d_invoct.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_INVOCATION_HH
#define D_INVOCATION_HH

//
//
// CONTENTS:
//
//		This file describes the C++ classes relating to a given Objective
//		Analyst invocation.
//
// REMARKS:
//
//		One transient instance of this class should be created for each
//		Objective Analyst invocation. Because we can only have one instance
//		of this class, all members will be static.
//
//		A given Objective Analyst invocation will operate upon zero, one or
//		more domains. Although conceptually the Domain collection for a given
//		invocation is contained within a given Invocation, the Domain
//		collection will not be kept here but within the Domain class.
//		However, we provide iterator and find functions here that
//		give the User the impression/illusion that they are maintained
//		within this class.
//
//		Note that the init() function provided by this class is the
//		highest level init function for the tool invocation.
//

// Include those header files that are DIRECTLY needed by this one.

#ifdef WIN32
  typedef int uid_t;
  typedef uid_t gid_t;
  typedef unsigned short mode_t;
#else
  #include <sys/types.h>
#endif


#include "u_typdef.hh"

#include <u_string.hh>

#include "d_typdef.hh"
#include "d_domid.hh"
#include "d_domain.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Invocation;

// Also declare classes in other subsystem that we reference but don't
// include the header files.


//
// CLASS: Invocation
//
// DESCRIPTION:
//
//		This defines the information needed for each Objective Analyst
//		invocation.
//
// REMARKS:
//
//		The instances of this class will always be transient. Since
//		only one of these will ever be created, we will make all
//		functions and data static so the User will not have to keep a
//		clumsy pointer to the single Invocation instance.
//		As a matter of fact, we won't even provide a constructor
//		since all data is static.
//

class Invocation
	{
	public:
		// MANAGER functions

		static void init();

		// IMPLEMENTOR functions

		// The following create and open functions return a Domain_id to
		// the Domain instance within the opened database. If this returned
		// id is NO_ID(0), then the create/open failed.
		//
		// The following is the full entire pathname of the OOA database
		// file to be created/opened. It must begin with a "/".

		static Domain_id open_database(
			const char *p_ooa_db_full_pathname, String &p_err_msg );

		// Iterator functions

		static Domain *first_domain();
		static Domain *next_domain();
		static void done_with_domain();

		static Domain_reference *first_domain_ref();
		static Domain_reference *next_domain_ref();
		static void done_with_domain_ref();

		// find/query functions.

		static Domain_reference *find_domain_ref_by_id(
			const Domain_id &p_domain_id);
		static Domain *find_domain_by_id( const Domain_id &p_domain_id );
		static Domain *find_domain_by_name( const char *p_name );

		// Version management helper functions.

		// If "multi_user_dbs()" returns FALSE, then using personal dbs

		static t_boolean multi_user_dbs();

		// ACCESS functions.

		static t_boolean get_debug_ASL()
			{ return debug_ASL; }
		static void set_debug_ASL( t_boolean p_debug_ASL )
			{ debug_ASL = p_debug_ASL; }

		static t_boolean get_user_rw_status( const char *p_full_file_name );
		static t_boolean get_user_rw_status( mode_t p_file_mode,
			uid_t p_file_uid, gid_t p_file_gid );

		static void set_current_domain_id( const Domain_id &p_domain_id )
			{ current_domain_id = p_domain_id; }

		static Domain_id get_current_domain_id()
			{ return current_domain_id; }

		static void insert_domain_ref( Domain_reference *p_domain_ref_ptr )
			{ domain_refs->insert( p_domain_ref_ptr ); }

		static mc_dbms_List< Domain_reference * > *get_domain_ref_coll_ptr()
			{ return domain_refs; }

		// HELPING functions

		static String get_syschar();
		static String get_syschar_text(const char *);
		static String get_locale();
		static t_boolean locale_ok(const char *);
		static t_boolean syschar_ok(const char *);

	private:
		// Don't even allow the constructors to be invoked by User

		Invocation() {}
		~Invocation() {}

		static t_boolean debug_ASL;

		static Domain_id current_domain_id;

		// The following collection allows us to model a TRANSIENT
		// class-extent of all Domains open for a given Invocation.
		// Via each Domain_reference, we can navigate to the corresponding
		// persistent Domain instance. The User doesn't even know about
		// this Domain_reference class; they just hold a Domain_id.

		static mc_dbms_List< Domain_reference * > *domain_refs;

		static mc_dbms_Cursor< Domain_reference *> *domain_refs_cursor_ptr;

	};


//
// The following FIRST/NEXT macros are to be used to get the indicated
// collection elements. FIRST/NEXT should be used in a "for" or "while"
// loop for which iteration will not be thru the entire collection.
// (Note that we need no instance pointer since we only have one
// Invocation which is static).
// Eg-
//
//	Domain *domain_ptr;
//
//	t_boolean found = FALSE;
//	FIRST_DOMAIN( domain_ptr, cursor1 );  // CANNOT be first part of "for"
//
//	for ( ;
//		  ( domain_ptr != 0 ) && ( found == FALSE );
//		  NEXT_DOMAIN( domain_ptr, cursor1 ) )
//		{
//		...
//		}
//
// or
//
//	FIRST_DOMAIN( domain_ptr, cursor1 );
//	while ( ( domain_ptr != 0 ) && ( ... ) )
//		{
//		...
//		NEXT_DOMAIN( domain_ptr, cursor1 );
//		}
//
// The FOR_ALL_... iteration macros should be used when you want to
// unconditionally and completely iterate thru an entire collection.
//
// Eg - 
//	Domain *domain_ptr;
//
//	FOR_ALL_DOMAINS( domain_ptr, cursor1 )
//		{
//		domain_ptr->print_data();
//		}
//

#define FIRST_DOMAIN_REF( domain_ref_ptr, cursor_name )	\
	mc_dbms_Cursor< Domain_reference * >	\
		cursor_name( *Invocation::get_domain_ref_coll_ptr(), mc_dbms_cursor::safe); \
	domain_ref_ptr = cursor_name.first();
	
#define NEXT_DOMAIN_REF( domain_ref_ptr, cursor_name )	\
	domain_ref_ptr = cursor_name.next()
	
#define FOR_ALL_DOMAIN_REFS( domain_ref_ptr, cursor_name )	\
	mc_dbms_Cursor< Domain_reference * >	\
		cursor_name( *Invocation::get_domain_ref_coll_ptr(), mc_dbms_cursor::safe); \
	for ( domain_ref_ptr = cursor_name.first(); \
		  domain_ref_ptr != 0; \
		  domain_ref_ptr = cursor_name.next() )


#define FIRST_DOMAIN( domain_ptr, cursor_name )	\
	mc_dbms_Cursor< Domain_reference * >	\
		cursor_name( *Invocation::get_domain_ref_coll_ptr(), mc_dbms_cursor::safe); \
	Domain_reference *_domain_ref_ptr = cursor_name.first(); \
	if ( _domain_ref_ptr != 0 )	\
		{	\
		domain_ptr = _domain_ref_ptr->get_domain_ptr();	\
		}	\
	else	\
		{	\
		domain_ptr = 0;	\
		}
	
#define NEXT_DOMAIN( domain_ptr, cursor_name )	\
	_domain_ref_ptr = cursor_name.next(); \
	if ( _domain_ref_ptr != 0 )	\
		{	\
		domain_ptr = _domain_ref_ptr->get_domain_ptr();	\
		}	\
	else	\
		{	\
		domain_ptr = 0;	\
		}
	
#define FOR_ALL_DOMAINS( domain_ptr, cursor_name )	\
	mc_dbms_Cursor< Domain_reference * >	\
		cursor_name( *Invocation::get_domain_ref_coll_ptr(), mc_dbms_cursor::safe); \
	for ( Domain_reference *_domain_ref_ptr = cursor_name.first(); \
		  ( _domain_ref_ptr != 0 ) && \
		  ( ( domain_ptr = _domain_ref_ptr->get_domain_ptr() ) != 0 ); \
		  _domain_ref_ptr = cursor_name.next() )

#endif

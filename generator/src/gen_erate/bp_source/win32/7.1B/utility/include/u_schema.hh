/*========================================================================
 *
 * File:      $RCSfile: u_schema.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

//
//  CONTENTS:
//	This file contains the schema (ie - class definitions) used by the
//	MC_DBMS application. When a user MC_DBMS uses the Library Interface (LI) as
//	opposed to Data Manipulation Language (DML), all classes declared by
//	the application must appear in this file, in addition to being in
//	their normal header file.
//
// REMARKS:
//	Any time the schema definition is added to this file, corresponding
//	entries MUST be added to typespecs.cc and typespecs.hh.
//
// 	Also note that the "dummy" function is not called from anywhere; this
// 	file must simply be compiled via the "ss7_schema_standin" directive
// 	in the corresponding Makefile.
//



#include "u_typdef.hh"
#include "u_id.hh"

#include "u_string.hh"
#include "u_id.hh"
#include "u_desc.hh"

#include "u_udmenu.hh"

// general-purpose utility classes

MC_DBMS_MARK_SCHEMA_TYPE( String );
MC_DBMS_MARK_SCHEMA_TYPE( Id );
MC_DBMS_MARK_SCHEMA_TYPE( Id_assigner );
MC_DBMS_MARK_SCHEMA_TYPE( Description );

MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<String*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<U_user_defined_menu*> );

MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Description*> );

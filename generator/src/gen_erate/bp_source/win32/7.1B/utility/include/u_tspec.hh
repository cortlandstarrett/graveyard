/*========================================================================
 *
 * File:      $RCSfile: u_tspec.hh,v $
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

#ifndef U_TSPEC_HH
#define U_TSPEC_HH


//
// CONTENTS:
//
//	This file contains the externed MC_DBMS typespecs so they can be easily
//	accessed without the user having to define them every time they do
//	an MC_DBMS new.
//
// REMARKS:
//
//	When a typespec is added to typespecs.cc, it should be added and
//	externed here also.
//





// Primitive typespecs
//
extern mc_dbms_typespec *char_type;
extern mc_dbms_typespec *int_type;
extern mc_dbms_typespec *vchar_type;

// General-purpose utility typespecs
//
extern mc_dbms_typespec *String_type;
extern mc_dbms_typespec *Id_type;
extern mc_dbms_typespec *Id_assigner_type;
extern mc_dbms_typespec *Description_type;

// MC_DBMS typespecs
//
extern mc_dbms_typespec *workspace_type;
extern mc_dbms_typespec *configuration_type;




#endif

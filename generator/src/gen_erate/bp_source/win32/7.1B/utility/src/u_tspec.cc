/*========================================================================
 *
 * File:      $RCSfile: u_tspec.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:58 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>
#include "u_id.hh"
#include "u_desc.hh"
//
// CONTENTS:
//
//	This file contains the definitions of all MC_DBMS typespecs, which simply
//	define a type variable for every C++ class.
//
// REMARKS:
//
//	Any time a new C++ class is added to schema.cc, a corresponding type-
//	spec should be defined here and also externed in typespecs.hh.
//


#include <vchar.h>

// Primitive typespecs

mc_dbms_typespec *char_type = new mc_dbms_typespec( "char",sizeof(char) );
mc_dbms_typespec *int_type = new mc_dbms_typespec( "int",sizeof(int) );

#if (vportVCHAR_CODESET == vportCODESET_ASCII)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_char();
#elif (vportVCHAR_CODESET == vportCODESET_LATIN_1)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_char();
#elif (vportVCHAR_CODESET == vportCODESET_MACINTOSH)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_char();
#elif (vportVCHAR_CODESET == vportCODESET_WINDOWS)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_char();
#elif (vportVCHAR_CODESET == vportCODESET_UNICODE)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_short();
#elif (vportVCHAR_CODESET == vportCODESET_MNLS)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_short();
#elif (vportVCHAR_CODESET == vportCODESET_ISO_10646)
mc_dbms_typespec *vchar_type = mc_dbms_typespec::get_unsigned_long();
#else
typedef _error _error;	/* (vportVCHAR_CODESET is unknown!) */
#endif

// General-purpose utility typespecs

mc_dbms_typespec *String_type = new mc_dbms_typespec( "String",sizeof(std::string) );

// OOA general-purpose utility typespecs

mc_dbms_typespec *Id_type = new mc_dbms_typespec( "Id",sizeof(Id) );
mc_dbms_typespec *Id_assigner_type = new mc_dbms_typespec( "Id_assigner",sizeof(Id_assigner) );
mc_dbms_typespec *Description_type = new mc_dbms_typespec( "Description",sizeof(Description) );

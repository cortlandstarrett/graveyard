/*========================================================================
 *
 * File:      $RCSfile: a_schema.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:39 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>
 

#include "a_bush.hh"

MC_DBMS_MARK_SCHEMA_TYPE( AL_Bush_action );
MC_DBMS_MARK_SCHEMA_TYPE( AL_Bush_statement );
MC_DBMS_MARK_SCHEMA_TYPE( AL_Bush_statement_component );
MC_DBMS_MARK_SCHEMA_TYPE( AL_Bush_literal );
MC_DBMS_MARK_SCHEMA_TYPE( AL_Bush_relocatable );

MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List< AL_Bush_statement*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<AL_Bush_statement_component*> );

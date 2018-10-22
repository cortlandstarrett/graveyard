/*========================================================================
 *
 * File:      $RCSfile: u_id.cc,v $
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


#include <u_id.hh>




const Id Id::Default = Id( 0, Id::NO_CLASS_TYPE, 0, 0 );

// i2778.3.1.2 begin
void
Id_assigner::update_next_value( t_uint p_value_id )
{
    if ( p_value_id > get_current_assigner_value_id() )
    {
        set_current_assigner_value_id( p_value_id );
    }
}
// i2778.3.1.2 end




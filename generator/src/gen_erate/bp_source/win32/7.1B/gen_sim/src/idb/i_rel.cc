/*========================================================================
 *
 * File:      $RCSfile: i_rel.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#include <DBU_utility.hh>
#include <D_typedefs.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>
#include <d_typdef.hh>
#endif


#include <i_rel.hh>
#include <i_rop.hh>





I_Relationship *
I_Relationship::create( mc_dbms_database * p_db_ptr
,
		const Description& p_number )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::create()" ));

I_Relationship * ptr = new( p_db_ptr, I_Relationship::get_mc_dbms_typespec() )
	I_Relationship(
		p_number );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::create()" ));

return( ptr );

}


I_Relationship::I_Relationship (const Description& p_number)
    :
    m_number (p_number)

{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::I_Relationship()" ));

    unsigned int entire_value = assign_next_id_value( mc_dbms_database::of (this) );
    m_relationship_ID.set_entire_value( entire_value );
    m_relationship_ID.set_class_type( RELATIONSHIP_TYPE );

get_class_extent_ptr( mc_dbms_database::of( this ) )->insert( this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::I_Relationship()" ));

}


I_Relationship::~I_Relationship ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::~I_Relationship()" ));

get_class_extent_ptr( mc_dbms_database::of( this ) )->remove( this );

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::~I_Relationship()" ));

}

mc_dbms_List< I_Relationship * > *
I_Relationship::get_class_extent_ptr( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::get_class_extent_ptr()" ));

mc_dbms_List< I_Relationship * > * class_extent_ptr;

mc_dbms_database_root * root_ptr = p_db_ptr->find_root( "I_Relationship_class_extent" );

if ( root_ptr )
{
	class_extent_ptr = ( mc_dbms_List< I_Relationship *> * )
		root_ptr->get_value();
}
else
{
    class_extent_ptr = & mc_dbms_List< I_Relationship * >::create
	(p_db_ptr);
	p_db_ptr->create_root( "I_Relationship_class_extent" )->
		set_value( class_extent_ptr );
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::get_class_extent_ptr()" ));

return( class_extent_ptr );

}
void
I_Relationship::relate_R2003( I_Related_Object_Pair * p_Related_Object_Pair_R2003_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::relate_R2003()" ));

m_Related_Object_Pair_R2003_coll.insert( p_Related_Object_Pair_R2003_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::relate_R2003()" ));

}



I_Relationship*
I_Relationship::find_Relationship_by_relationship_ID(
	mc_dbms_database * p_db_ptr, const Id & p_relationship_ID )
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Relationship::find_Relationship_by_relationship_ID ()"));


    mc_dbms_Cursor< I_Relationship * > cursor(
	    * I_Relationship::get_class_extent_ptr( p_db_ptr ) );
    I_Relationship * ptr = cursor.first();


    I_Relationship* found_rel_ptr = 0;
    I_Relationship* rel_ptr = cursor.first ();
    while (rel_ptr)
    {
	if (rel_ptr->get_relationship_ID () == p_relationship_ID )
	{
	    if (! found_rel_ptr)
	    {
		found_rel_ptr = rel_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one I_Relationship with same ID exists in GEN/SIM DB."));
	    }
	}
	rel_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Relationship::find_Relationship_by_relationship_ID ()"));


    return (found_rel_ptr);
}


mc_dbms_Set< I_Relationship * > *
I_Relationship::find_Relationship_by_number(
	mc_dbms_database * p_db_ptr, const Description& p_number )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Relationship::find_Relationship_by_number()" ));

mc_dbms_Set< I_Relationship * > * coll_ptr =
	& mc_dbms_Set< I_Relationship * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_Relationship * > cursor(
	* I_Relationship::get_class_extent_ptr( p_db_ptr ) );
I_Relationship * ptr = cursor.first();

while ( ptr )
{
	if ( ptr->get_number() == p_number )
	{
		coll_ptr->insert( ptr );
	}
	ptr = cursor.next();
}
LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Relationship::find_Relationship_by_number()" ));

return( coll_ptr );

}




mc_dbms_relationship_m_1_body(I_Relationship,m_Related_Object_Pair_R2003_coll,I_Related_Object_Pair,m_Relationship_R2003_ptr);


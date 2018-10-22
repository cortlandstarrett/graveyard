/*========================================================================
 *
 * File:      $RCSfile: i_roip.cc,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>
#include <u_cursor.hh>                               


#include <i_roip.hh>
#include <i_rop.hh>
#include <i_oinst.hh>





I_Related_Object_Instance_Pair *
I_Related_Object_Instance_Pair::create( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::create()" ));

I_Related_Object_Instance_Pair * ptr = new( p_db_ptr, I_Related_Object_Instance_Pair::get_mc_dbms_typespec() )
	I_Related_Object_Instance_Pair();

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::create()" ));

return( ptr );

}


I_Related_Object_Instance_Pair::I_Related_Object_Instance_Pair (bool  isBeingRestored)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Related_Object_Instance_Pair::I_Related_Object_Instance_Pair ()."));

	/**
	 * When we are restoring this instance data from disk we don't want to perform any
	 * of these operations.
	 */
	if (!isBeingRestored) {
	    unsigned int entire_value = assign_next_id_value (mc_dbms_database::of (this));
	    m_rel_inst_ID.set_entire_value (entire_value);
	    m_rel_inst_ID.set_class_type (RELATIONSHIP_INST_TYPE);
	
	    m_relationship_ID.set_class_type (RELATIONSHIP_TYPE);
	
	    m_Related_Object_Pair_R2004_ptr.relate( 0, this );
	    m_Object_Instance_R2010_ptr.relate( 0, this );
	    m_Object_Instance_R2011_ptr.relate( 0, this );
	
	    //  Place in class extent in order by ID.  Just to make sure, call set
	    //    of the rel_inst_ID to re-insert this ROIP.
	    //
	    get_class_extent_ptr (mc_dbms_database::of (this))->insert_last (this);
	    set_rel_inst_ID (m_rel_inst_ID);
	}

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted  I_Related_Object_Instance_Pair::I_Related_Object_Instance_Pair ()."));
}


I_Related_Object_Instance_Pair::~I_Related_Object_Instance_Pair ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::~I_Related_Object_Instance_Pair()" ));

    get_class_extent_ptr( mc_dbms_database::of( this ) )->remove( this );

    m_Related_Object_Pair_R2004_ptr.relate( 0, this );
    m_Object_Instance_R2010_ptr.relate( 0, this );
    m_Object_Instance_R2011_ptr.relate( 0, this );

    operator delete( this, ""); // Remove from InstanceTracker
    
	LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::~I_Related_Object_Instance_Pair()" ));

}

mc_dbms_List< I_Related_Object_Instance_Pair * > *
I_Related_Object_Instance_Pair::get_class_extent_ptr( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::get_class_extent_ptr()" ));

mc_dbms_List< I_Related_Object_Instance_Pair * > * class_extent_ptr;

mc_dbms_database_root * root_ptr = p_db_ptr->find_root( "I_Related_Object_Instance_Pair_class_extent" );

if ( root_ptr )
{
	class_extent_ptr = ( mc_dbms_List< I_Related_Object_Instance_Pair *> * )
		root_ptr->get_value();
}
else
{
    class_extent_ptr = & mc_dbms_List< I_Related_Object_Instance_Pair * >::create
	(p_db_ptr);
	p_db_ptr->create_root( "I_Related_Object_Instance_Pair_class_extent" )->
		set_value( class_extent_ptr );
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::get_class_extent_ptr()" ));

return( class_extent_ptr );

}




void
I_Related_Object_Instance_Pair::relate_R2004( I_Related_Object_Pair * p_Related_Object_Pair_R2004_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::relate_R2004()" ));

m_Related_Object_Pair_R2004_ptr.relate( p_Related_Object_Pair_R2004_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::relate_R2004()" ));

}

void
I_Related_Object_Instance_Pair::relate_R2010( I_Object_Instance * p_Object_Instance_R2010_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::relate_R2010()" ));

m_Object_Instance_R2010_ptr.relate( p_Object_Instance_R2010_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::relate_R2010()" ));

}

void
I_Related_Object_Instance_Pair::relate_R2011( I_Object_Instance * p_Object_Instance_R2011_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Instance_Pair::relate_R2011()" ));

m_Object_Instance_R2011_ptr.relate( p_Object_Instance_R2011_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::relate_R2011()" ));

}





mc_dbms_List< I_Related_Object_Instance_Pair * > * 
I_Related_Object_Instance_Pair::find_Related_Object_Instance_Pair_by_relationship_ID
    (mc_dbms_database * p_db_ptr, const Id & p_relationship_ID)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Related_Object_Instance_Pair::find_Related_Object_Instance_Pair_by_relationship_ID ()"));

mc_dbms_List< I_Related_Object_Instance_Pair * > * roip_coll_ptr =
	& mc_dbms_List< I_Related_Object_Instance_Pair * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_Related_Object_Instance_Pair * > roip_cursor(
	* I_Related_Object_Instance_Pair::get_class_extent_ptr( p_db_ptr ) );
I_Related_Object_Instance_Pair * roip_ptr = roip_cursor.first();

while ( roip_ptr )
{
	if (roip_ptr->get_relationship_ID () == p_relationship_ID)
	{
		roip_coll_ptr->insert_last( roip_ptr );
	}
	roip_ptr = roip_cursor.next();
}
LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::find_Object_by_key_letter()" ));

return( roip_coll_ptr );

}





mc_dbms_List< I_Related_Object_Instance_Pair * > * 
I_Related_Object_Instance_Pair::find_Related_Object_Instance_Pair_by_rel_inst_ID
    (mc_dbms_database * p_db_ptr, const Id & p_rel_inst_ID)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Related_Object_Instance_Pair::find_Related_Object_Instance_Pair_by_rel_inst_ID ()"));

mc_dbms_List< I_Related_Object_Instance_Pair * > * roip_coll_ptr =
	& mc_dbms_List< I_Related_Object_Instance_Pair * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_Related_Object_Instance_Pair * > roip_cursor(
	* I_Related_Object_Instance_Pair::get_class_extent_ptr( p_db_ptr ) );
I_Related_Object_Instance_Pair * roip_ptr = roip_cursor.first();

while ( roip_ptr )
{
	if (roip_ptr->get_rel_inst_ID () == p_rel_inst_ID)
	{
		roip_coll_ptr->insert_last( roip_ptr );
	}
	roip_ptr = roip_cursor.next();
}
LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Instance_Pair::find_Object_by_key_letter()" ));

return( roip_coll_ptr );

}





void
I_Related_Object_Instance_Pair::set_rel_inst_ID (const Id& p_input)

{
#ifdef ORDERING_OF_CLASS_EXTENT_NEEDED
    mc_dbms_List<I_Related_Object_Instance_Pair*>* roip_coll_ptr =
	get_class_extent_ptr (mc_dbms_database::of (this));
#endif
    m_rel_inst_ID = p_input;
#ifdef ORDERING_OF_CLASS_EXTENT_NEEDED
    roip_coll_ptr->remove (this);

    I_Related_Object_Instance_Pair* roip_ptr;
    int roip_position = 0;
    FOR_ALL_ELEMENTS_SAFE
	(roip_ptr,
	I_Related_Object_Instance_Pair,
	roip_coll_ptr,
	roip_cursor)
    {
	if (roip_ptr->m_rel_inst_ID.get_entire_value ()
	    > m_rel_inst_ID.get_entire_value ())
	{
	    roip_coll_ptr->insert_before (this, roip_position);
	    return;
	}
	roip_position++;
    }

    roip_coll_ptr->insert_last (this);
#endif
}






mc_dbms_relationship_1_m_body(I_Related_Object_Instance_Pair,m_Related_Object_Pair_R2004_ptr,I_Related_Object_Pair,m_Related_Object_Instance_Pair_R2004_coll);

mc_dbms_relationship_1_m_body(I_Related_Object_Instance_Pair,m_Object_Instance_R2010_ptr,I_Object_Instance,m_Related_Object_Instance_Pair_R2010_coll);

mc_dbms_relationship_1_m_body(I_Related_Object_Instance_Pair,m_Object_Instance_R2011_ptr,I_Object_Instance,m_Related_Object_Instance_Pair_R2011_coll);


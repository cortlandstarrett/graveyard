/*========================================================================
 *
 * File:      $RCSfile: i_obj.cc,v $
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
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>


#include <i_obj.hh>
#include <i_attr.hh>
#include <i_oinst.hh>
#include <i_rop.hh>





I_Object *
I_Object::create( mc_dbms_database * p_db_ptr, const Description& p_key_letter )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::create()" ));

I_Object * ptr = new( p_db_ptr, I_Object::get_mc_dbms_typespec() )
	I_Object( p_key_letter );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::create()" ));

return( ptr );

}


I_Object::I_Object (const Description& p_key_letter)
    :
    m_key_letter (p_key_letter)

{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::I_Object()" ));

    unsigned int entire_value = assign_next_id_value( mc_dbms_database::of (this) );
    m_object_ID.set_entire_value( entire_value );
    m_object_ID.set_class_type( OBJECT_TYPE );

get_class_extent_ptr( mc_dbms_database::of( this ) )->insert( this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::I_Object()" ));

}


I_Object::~I_Object ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::~I_Object()" ));

get_class_extent_ptr( mc_dbms_database::of( this ) )->remove( this );

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::~I_Object()" ));

}

mc_dbms_List< I_Object * > *
I_Object::get_class_extent_ptr( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::get_class_extent_ptr()" ));

mc_dbms_List< I_Object * > * class_extent_ptr;

mc_dbms_database_root * root_ptr = p_db_ptr->find_root( "I_Object_class_extent" );

if ( root_ptr )
{
	class_extent_ptr = ( mc_dbms_List< I_Object *> * )
		root_ptr->get_value();
}
else
{
    class_extent_ptr = & mc_dbms_List< I_Object * >::create
      (p_db_ptr);
	p_db_ptr->create_root( "I_Object_class_extent" )->
		set_value( class_extent_ptr );
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::get_class_extent_ptr()" ));

return( class_extent_ptr );

}
void
I_Object::relate_R102( I_Attribute * p_Attribute_R102_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R102()" ));

m_Attribute_R102_coll.insert( p_Attribute_R102_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R102()" ));

}
void
I_Object::relate_R102A( I_Attribute * p_Attribute_R102A_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R102A()" ));

m_Attribute_R102A_ptr = p_Attribute_R102A_ptr;

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R102A()" ));

}

void
I_Object::relate_R2001( I_Object_Instance * p_Object_Instance_R2001_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R2001()" ));

m_Object_Instance_R2001_coll.insert( p_Object_Instance_R2001_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R2001()" ));

}

void
I_Object::relate_R2001A( I_Object_Instance * p_Object_Instance_R2001A_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R2001A()" ));

m_Object_Instance_R2001A_ptr = p_Object_Instance_R2001A_ptr;

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R2001A()" ));

}

void
I_Object::relate_R2006( I_Related_Object_Pair * p_Related_Object_Pair_R2006_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R2006()" ));

m_Related_Object_Pair_R2006_coll.insert( p_Related_Object_Pair_R2006_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R2006()" ));

}

void
I_Object::relate_R2005( I_Related_Object_Pair * p_Related_Object_Pair_R2005_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::relate_R2005()" ));

m_Related_Object_Pair_R2005_coll.insert( p_Related_Object_Pair_R2005_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::relate_R2005()" ));

}



I_Object*
I_Object::find_Object_by_object_ID
    (mc_dbms_database * p_db_ptr, const Id & p_object_ID)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object::find_Object_by_object_ID ()"));


    mc_dbms_Cursor< I_Object * > cursor
	(*I_Object::get_class_extent_ptr (p_db_ptr));


    I_Object* found_obj_ptr = 0;
    I_Object* obj_ptr = cursor.first ();
    while (obj_ptr)
    {
	if (obj_ptr->get_object_ID () == p_object_ID)
	{
	    if (! found_obj_ptr)
	    {
		found_obj_ptr = obj_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one object with same ID exists in OOA DB."));
	    }
	}
	obj_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object::find_Object_by_object_ID ()"));


    return (found_obj_ptr);
}


mc_dbms_Set< I_Object * > *
I_Object::find_Object_by_key_letter(
	mc_dbms_database * p_db_ptr, const Description& p_key_letter )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::find_Object_by_key_letter()" ));

mc_dbms_Set< I_Object * > * coll_ptr =
	& mc_dbms_Set< I_Object * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_Object * > cursor(
	* I_Object::get_class_extent_ptr( p_db_ptr ) );
I_Object * ptr = cursor.first();

while ( ptr )
{
	if ( ptr->get_key_letter() == p_key_letter )
	{
		coll_ptr->insert( ptr );
	}
	ptr = cursor.next();
}
LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::find_Object_by_key_letter()" ));

return( coll_ptr );

}





I_Attribute*
I_Object::find_Attribute_R102_by_attribute_ID (const Id& p_attribute_ID) const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object::find_Attribute_R102_by_attribute_ID ()"));


    mc_dbms_Cursor< I_Attribute * > cursor( m_Attribute_R102_coll );
    I_Attribute * ptr = cursor.first();


    I_Attribute* found_attr_ptr = 0;
    I_Attribute* attr_ptr = cursor.first ();
    while (attr_ptr)
    {
	if (attr_ptr->get_attribute_ID () == p_attribute_ID)
	{
	    if (! found_attr_ptr)
	    {
		found_attr_ptr = attr_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one Attribute with same ID related to same Object exists in OOA DB."));
	    }
	}
	attr_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object::find_Attribute_R102_by_attribute_ID ()"));


    return (found_attr_ptr);
}


mc_dbms_Set< I_Attribute * > *
I_Object::find_Attribute_R102_by_name(
		const Description& p_name ) const
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object::find_Attribute_R102_by_name()" ));

mc_dbms_Set< I_Attribute * > * coll_ptr =
	& mc_dbms_Set< I_Attribute * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_Attribute * > cursor( m_Attribute_R102_coll );
I_Attribute * ptr = cursor.first();

while ( ptr )
{
	if ( ptr->get_name() == p_name )
	{
		coll_ptr->insert( ptr );
	}
	ptr = cursor.next();
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object::find_Attribute_R102_by_name()" ));

return( coll_ptr );

}





I_Object_Instance*
I_Object::find_Object_Instance_R2001_by_object_instance_ID
    (const Id& p_object_instance_ID) const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object::find_Object_Instance_R2001_by_object_instance_ID ()"));


    mc_dbms_Cursor< I_Object_Instance * > cursor( m_Object_Instance_R2001_coll );
    I_Object_Instance * ptr = cursor.first();


    I_Object_Instance* found_oinst_ptr = 0;
    I_Object_Instance* oinst_ptr = cursor.first ();
    while (oinst_ptr)
    {
	if (oinst_ptr->get_object_instance_ID () == p_object_instance_ID)
	{
	    if (! found_oinst_ptr)
	    {
		found_oinst_ptr = oinst_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one I_Object_Instance with same ID related to same I_Object exists in GEN/SIM DB."));
	    }
	}
	oinst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object::find_Object_Instance_R2001_by_object_instance_ID ()"));


    return (found_oinst_ptr);
}




mc_dbms_relationship_m_1_body(I_Object,m_Attribute_R102_coll,I_Attribute,m_Object_R102_ptr);

mc_dbms_relationship_1_1_body(I_Object,m_Attribute_R102A_ptr,I_Attribute,m_Object_R102A_ptr);

mc_dbms_relationship_m_1_body(I_Object,m_Object_Instance_R2001_coll,I_Object_Instance,m_Object_R2001_ptr);

mc_dbms_relationship_1_1_body(I_Object,m_Object_Instance_R2001A_ptr,I_Object_Instance,m_Object_R2001A_ptr);

mc_dbms_relationship_m_1_body(I_Object,m_Related_Object_Pair_R2006_coll,I_Related_Object_Pair,m_Object_R2006_ptr);

mc_dbms_relationship_m_1_body(I_Object,m_Related_Object_Pair_R2005_coll,I_Related_Object_Pair,m_Object_R2005_ptr);

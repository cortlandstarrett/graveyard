/*========================================================================
 *
 * File:      $RCSfile: i_evt.cc,v $
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
#else
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>
#endif


#include <i_evt.hh>
#include <i_esdi.hh>
#include <i_einst.hh>
#include <i_rop.hh>
#include <i_rop.hh>





I_SM_Evt *
I_SM_Evt::create (mc_dbms_database* p_db_ptr, const Description& p_label)
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::create()" ));

I_SM_Evt * ptr = new( p_db_ptr, I_SM_Evt::get_mc_dbms_typespec() )
	I_SM_Evt(
		p_label );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::create()" ));

return( ptr );

}


I_SM_Evt::I_SM_Evt (const Description& p_label)
    :
    m_label (p_label)

{
LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
	(L_log_string, "Entered I_SM_Evt::I_SM_Evt ()."));

    unsigned int entire_value = assign_next_id_value( mc_dbms_database::of (this) );
    m_SM_evt_ID.set_entire_value( entire_value );
    m_SM_evt_ID.set_class_type( EVENT_TYPE );

get_class_extent_ptr( mc_dbms_database::of( this ) )->insert( this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::I_SM_Evt()" ));

}


I_SM_Evt::~I_SM_Evt ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::~I_SM_Evt()" ));

get_class_extent_ptr( mc_dbms_database::of( this ) )->remove( this );

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::~I_SM_Evt()" ));

}

mc_dbms_List< I_SM_Evt * > *
I_SM_Evt::get_class_extent_ptr( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::get_class_extent_ptr()" ));

mc_dbms_List< I_SM_Evt * > * class_extent_ptr;

mc_dbms_database_root * root_ptr = p_db_ptr->find_root( "I_SM_Evt_class_extent" );

if ( root_ptr )
{
	class_extent_ptr = ( mc_dbms_List< I_SM_Evt *> * )
		root_ptr->get_value();
}
else
{
    class_extent_ptr = & mc_dbms_List< I_SM_Evt * >::create
	(p_db_ptr);

    p_db_ptr->create_root( "I_SM_Evt_class_extent" )->
	set_value( class_extent_ptr );
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::get_class_extent_ptr()" ));

return( class_extent_ptr );

}
void
I_SM_Evt::relate_R2021( I_SM_Evt_Supp_DI * p_SM_Evt_Supp_DI_R2021_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::relate_R2021()" ));

m_SM_Evt_Supp_DI_R2021_coll.insert( p_SM_Evt_Supp_DI_R2021_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::relate_R2021()" ));

}

void
I_SM_Evt::relate_R2022( I_SM_Evt_Inst * p_SM_Evt_Inst_R2022_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::relate_R2022()" ));

m_SM_Evt_Inst_R2022_coll.insert( p_SM_Evt_Inst_R2022_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::relate_R2022()" ));

}


I_SM_Evt*
I_SM_Evt::find_SM_Evt_by_SM_evt_ID(
	mc_dbms_database * p_db_ptr, const Id& p_SM_evt_ID )
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt::find_SM_Evt_by_SM_evt_ID ()"));


    mc_dbms_Cursor< I_SM_Evt * > cursor
	(*I_SM_Evt::get_class_extent_ptr (p_db_ptr));


    I_SM_Evt* found_evt_ptr = 0;
    I_SM_Evt* evt_ptr = cursor.first ();
    while (evt_ptr)
    {
	if (evt_ptr->get_SM_evt_ID () == p_SM_evt_ID)
	{
	    if (! found_evt_ptr)
	    {
		found_evt_ptr = evt_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one event with same ID exists in OOA DB."));
	    }
	}
	evt_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt::find_SM_Evt_by_SM_evt_ID ()"));


    return (found_evt_ptr);
}


mc_dbms_Set< I_SM_Evt * > *
I_SM_Evt::find_SM_Evt_by_label(
	mc_dbms_database * p_db_ptr, const Description& p_label )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::find_SM_Evt_by_label()" ));

mc_dbms_Set< I_SM_Evt * > * coll_ptr =
	& mc_dbms_Set< I_SM_Evt * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_SM_Evt * > cursor(
	* I_SM_Evt::get_class_extent_ptr( p_db_ptr ) );
I_SM_Evt * ptr = cursor.first();

while ( ptr )
{
	if ( ptr->get_label() == p_label )
	{
		coll_ptr->insert( ptr );
	}
	ptr = cursor.next();
}
LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::find_SM_Evt_by_label()" ));

return( coll_ptr );

}


I_SM_Evt_Supp_DI*
I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_SM_esdi_ID(
		const Id& p_SM_esdi_ID ) const
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_SM_esdi_ID ()"));


    mc_dbms_Cursor< I_SM_Evt_Supp_DI * > cursor( m_SM_Evt_Supp_DI_R2021_coll );


    I_SM_Evt_Supp_DI* found_SM_esdi_ptr = 0;
    I_SM_Evt_Supp_DI* SM_esdi_ptr = cursor.first ();
    while (SM_esdi_ptr)
    {
	if (SM_esdi_ptr->get_SM_esdi_ID () == p_SM_esdi_ID)
	{
	    if (! found_SM_esdi_ptr)
	    {
		found_SM_esdi_ptr = SM_esdi_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one Attribute with same ID related to same Object exists in OOA DB."));
	    }
	}
	SM_esdi_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_SM_esdi_ID ()"));


    return (found_SM_esdi_ptr);
}


mc_dbms_Set< I_SM_Evt_Supp_DI * > *
I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_name(
		const Description& p_name ) const
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_name()" ));

mc_dbms_Set< I_SM_Evt_Supp_DI * > * coll_ptr =
	& mc_dbms_Set< I_SM_Evt_Supp_DI * >::create
	(mc_dbms_database::get_transient_database());

mc_dbms_Cursor< I_SM_Evt_Supp_DI * > cursor( m_SM_Evt_Supp_DI_R2021_coll );
I_SM_Evt_Supp_DI * ptr = cursor.first();

while ( ptr )
{
	if ( ptr->get_name() == p_name )
	{
		coll_ptr->insert( ptr );
	}
	ptr = cursor.next();
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt::find_SM_Evt_Supp_DI_R2021_by_name()" ));

return( coll_ptr );

}





I_SM_Evt_Inst*
I_SM_Evt::find_SM_Evt_Inst_R2022_by_evt_inst_ID
    (const Id& p_evt_inst_ID) const
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt::find_SM_Evt_Inst_R2022_by_evt_inst_ID ()"));


    mc_dbms_Cursor< I_SM_Evt_Inst * > cursor (m_SM_Evt_Inst_R2022_coll);


    I_SM_Evt_Inst* found_einst_ptr = 0;
    I_SM_Evt_Inst* einst_ptr = cursor.first ();
    while (einst_ptr)
    {
	if (einst_ptr->get_evt_inst_ID () == p_evt_inst_ID)
	{
	    if (! found_einst_ptr)
	    {
		found_einst_ptr = einst_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one I_SM_Evt_Inst with same ID related to same I_SM_Evt in GEN/SIM DB."));
	    }
	}
	einst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt::find_SM_Evt_Inst_R2022_by_evt_inst_ID ()"));


    return (found_einst_ptr);
}



mc_dbms_relationship_m_1_body(I_SM_Evt,m_SM_Evt_Supp_DI_R2021_coll,I_SM_Evt_Supp_DI,m_SM_Evt_R2021_ptr);

mc_dbms_relationship_m_1_body(I_SM_Evt,m_SM_Evt_Inst_R2022_coll,I_SM_Evt_Inst,m_SM_Evt_R2022_ptr);


/*========================================================================
 *
 * File:      $RCSfile: i_oinst.cc,v $
 * Version:   $Revision: 1.11 $
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

#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_einst.hh>
#include <i_obj.hh>
#include <i_roip.hh>
#include <d_object.hh>
#include <d_attr.hh>
#include <gs_find.hh>

extern mc_dbms_database*		GS_gen_sim_db_ptr;





I_Object_Instance *
I_Object_Instance::create( mc_dbms_segment * p_segment_ptr,
		t_uint p_related_flag )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::create()" ));

I_Object_Instance * ptr = new( p_segment_ptr, I_Object_Instance::get_mc_dbms_typespec() )
	I_Object_Instance(
		p_related_flag );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::create()" ));

return( ptr );

}


I_Object_Instance::I_Object_Instance (t_uint p_related_flag)
    :
    m_related_flag (p_related_flag)

{

    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered  I_Object_Instance::I_Object_Instance ()."));


    unsigned int entire_value = 0;
    {
	Id_assigner* id_assigner_ptr;
	mc_dbms_database_root* root_ptr
	    = GS_gen_sim_db_ptr->find_root ("OINST_Id_assigner");

	if (root_ptr)
	{
	    id_assigner_ptr = (Id_assigner*) root_ptr->get_value ();
	}
	else
	{
	    mc_dbms_typespec* id_assigner_type = new mc_dbms_typespec ("Id_assigner",sizeof(Id_assigner));
	    id_assigner_ptr = new (GS_gen_sim_db_ptr, id_assigner_type)
		Id_assigner (0,0,0,0);
	    GS_gen_sim_db_ptr->create_root ("OINST_Id_assigner")->
		set_value (id_assigner_ptr);
	}
	Id new_id = id_assigner_ptr->assign_next_id();
	entire_value = new_id.get_entire_value ();
    }
    m_object_instance_ID.set_entire_value (entire_value);
    m_object_instance_ID.set_class_type (OBJECT_INST_TYPE);


m_Object_R2001_ptr.relate( 0, this );
m_Object_R2001A_ptr = 0;

get_class_extent_ptr( mc_dbms_database::of( this ) )->insert( this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::I_Object_Instance()" ));

}


I_Object_Instance::~I_Object_Instance ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::~I_Object_Instance()" ));

get_class_extent_ptr( mc_dbms_database::of( this ) )->remove( this );

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::~I_Object_Instance()" ));

}

mc_dbms_List< I_Object_Instance * > *
I_Object_Instance::get_class_extent_ptr( mc_dbms_database * p_db_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::get_class_extent_ptr()" ));

mc_dbms_List< I_Object_Instance * > * class_extent_ptr;

mc_dbms_database_root * root_ptr = p_db_ptr->find_root( "I_Object_Instance_class_extent" );

if ( root_ptr )
{
	class_extent_ptr = ( mc_dbms_List< I_Object_Instance *> * )
		root_ptr->get_value();
}
else
{
    class_extent_ptr = & mc_dbms_List< I_Object_Instance * >::create
	(p_db_ptr);
	p_db_ptr->create_root( "I_Object_Instance_class_extent" )->
		set_value( class_extent_ptr );
}

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::get_class_extent_ptr()" ));

return( class_extent_ptr );

}
void
I_Object_Instance::relate_R2002( I_Attribute_Instance * p_Attribute_Instance_R2002_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::relate_R2002()" ));

m_Attribute_Instance_R2002_coll.insert( p_Attribute_Instance_R2002_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::relate_R2002()" ));

}

void
I_Object_Instance::relate_R2001( I_Object * p_Object_R2001_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::relate_R2001()" ));

m_Object_R2001_ptr.relate( p_Object_R2001_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::relate_R2001()" ));

}

void
I_Object_Instance::relate_R2001A( I_Object * p_Object_R2001A_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::relate_R2001A()" ));

m_Object_R2001A_ptr = p_Object_R2001A_ptr;

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::relate_R2001A()" ));

}

void
I_Object_Instance::relate_R2010( I_Related_Object_Instance_Pair * p_Related_Object_Instance_Pair_R2010_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::relate_R2010()" ));

m_Related_Object_Instance_Pair_R2010_coll.insert( p_Related_Object_Instance_Pair_R2010_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::relate_R2010()" ));

}

void
I_Object_Instance::relate_R2011( I_Related_Object_Instance_Pair * p_Related_Object_Instance_Pair_R2011_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Object_Instance::relate_R2011()" ));

m_Related_Object_Instance_Pair_R2011_coll.insert( p_Related_Object_Instance_Pair_R2011_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Object_Instance::relate_R2011()" ));

}





void
I_Object_Instance::relate_R2031 (I_SM_Evt_Inst* p_einst_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
	(L_log_string, "Entered I_Object_Instance::relate_R2031 ()."));


    t_boolean inserted = FALSE;
    for (t_uint curr_einst_pos = 0;
	((! inserted)
	    && (curr_einst_pos < m_SM_Evt_Inst_R2031_coll.cardinality ()));
	curr_einst_pos++)
    {
        I_SM_Evt_Inst* curr_einst_ptr
	    = m_SM_Evt_Inst_R2031_coll.retrieve (curr_einst_pos);
	if (curr_einst_ptr->get_expiration_time ()
	    > p_einst_ptr->get_expiration_time ())
	{
	    m_SM_Evt_Inst_R2031_coll.insert_before
		(p_einst_ptr, curr_einst_pos);
	    inserted = TRUE;
	}
    }
    if (! inserted)
    {
	m_SM_Evt_Inst_R2031_coll.insert_last (p_einst_ptr);
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END,
	(L_log_string, "Exitted I_Object_Instance::relate_R2031 ()."));
}





void
I_Object_Instance::relate_R2032 (I_SM_Evt_Inst* p_einst_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN,
	(L_log_string, "Entered I_Object_Instance::relate_R2032 ()."));


    t_boolean inserted = FALSE;
    for (t_uint curr_einst_pos = 0;
	((! inserted)
	    && (curr_einst_pos < m_SM_Evt_Inst_R2032_coll.cardinality ()));
	curr_einst_pos++)
    {
        I_SM_Evt_Inst* curr_einst_ptr
	    = m_SM_Evt_Inst_R2032_coll.retrieve (curr_einst_pos);
	if (curr_einst_ptr->get_expiration_time ()
	    > p_einst_ptr->get_expiration_time ())
	{
	    m_SM_Evt_Inst_R2032_coll.insert_before
		(p_einst_ptr, curr_einst_pos);
	    inserted = TRUE;
	}
    }
    if (! inserted)
    {
	m_SM_Evt_Inst_R2032_coll.insert_last (p_einst_ptr);
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END,
	(L_log_string, "Exitted I_Object_Instance::relate_R2032 ()."));
}





I_Object_Instance*
I_Object_Instance::find_Object_Instance_by_object_instance_ID
    (mc_dbms_database * p_db_ptr, const Id & p_object_instance_ID)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object_Instance::find_Object_Instance_by_object_instance_ID ()"));


    mc_dbms_Cursor< I_Object_Instance * > cursor
	(*I_Object_Instance::get_class_extent_ptr (p_db_ptr));


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
		    "More than one I_Object_Instance with same ID exists in GEN/SIM DB."));
	    }
	}
	oinst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object_Instance::find_Object_Instance_by_object_instance_ID ()"));


    return (found_oinst_ptr);
}




I_Attribute_Instance*
I_Object_Instance::find_Attribute_Instance_R2002_by_attribute_ID
    (const Id& p_attribute_ID) const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object_Instance::find_Attribute_Instance_R2002_by_attribute_ID ()"));


    mc_dbms_Cursor<I_Attribute_Instance*> cursor (m_Attribute_Instance_R2002_coll);


    I_Attribute_Instance* found_attr_inst_ptr = 0;
    I_Attribute_Instance* attr_inst_ptr = cursor.first ();
    while (attr_inst_ptr)
    {
	if (attr_inst_ptr->get_attribute_ID () == p_attribute_ID)
	{
	    if (! found_attr_inst_ptr)
	    {
		found_attr_inst_ptr = attr_inst_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one Attribute Instance with same ID related to same Object Instance exists in OOA DB."));
	    }
	}
	attr_inst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object_Instance::find_Attribute_Instance_R2002_by_attribute_ID ()"));


    return (found_attr_inst_ptr);
}




I_Attribute_Instance*
I_Object_Instance::find_Attribute_Instance_R2002_by_core_data_type
    (t_core_data_type p_core_data_type) const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Object_Instance::find_Attribute_Instance_R2002_by_core_data_type (p_core_data_type=%d)",
	p_core_data_type));


    mc_dbms_Cursor<I_Attribute_Instance*> cursor (m_Attribute_Instance_R2002_coll);


    I_Attribute_Instance* found_attr_inst_ptr = 0;
    I_Attribute_Instance* attr_inst_ptr = cursor.first ();
    while (attr_inst_ptr)
    {
	if (attr_inst_ptr->get_core_data_type () == p_core_data_type)
	{
	    if (! found_attr_inst_ptr)
	    {
		found_attr_inst_ptr = attr_inst_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one Attribute Instance with same core_data_type related to same Object Instance exists in OOA DB."));
	    }
	}
	attr_inst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Object_Instance::find_Attribute_Instance_R2002_by_core_data_type ()"));


    return (found_attr_inst_ptr);
}



t_boolean appendIDs(int idNum,Description &str,mc_dbms_Cursor< I_Attribute_Instance *> *cur)
{
    t_boolean foundId=FALSE;
	cur->first();
	while(!cur->null()){
		I_Attribute_Instance *ai= cur->retrieve();
		if(ai){
    		Id att_id=ai->get_attribute_ID ();    
            Attribute* a=GS_find::find_attribute_by_id(att_id);
            if(a && a->is_an_identifier()){
	            Object_identifier_attribute * oia = a->find_object_id_attr(idNum);
	            if(oia){
		            I_var* iv = ai->get_var_ptr ();
                    if(iv){
				        if(foundId) str += ", "; 
				        foundId=TRUE;
			            str += a->get_attr_name();
			            str += "='";
			            str +=iv->get_value_str ();
			            str += "'";
				    }
				}
			}
		}
		cur->next();
	}
	return foundId;
}

void I_Object_Instance::appendObjectIdAttributes(Description &str)
{
     mc_dbms_List< I_Attribute_Instance * > *al=get_Attribute_Instance_R2002_coll_ptr();
     if(al){
		mc_dbms_Cursor< I_Attribute_Instance *> *cur=new mc_dbms_Cursor<  I_Attribute_Instance * >( *al, mc_dbms_cursor::safe);
		t_boolean found;
		for(int i=0;i<3;i++){
		    Description d=" *";
		    d.append_char('1'+i);
		    d+="(";
		    found=appendIDs(i,d,cur);
		    if(found) {
		       d+=")";
		       str += d;
		       break;
		    }   
		}
		delete cur;
     }
}

void I_Object_Instance::toString(Description &str){
	if (get_Object_R2001_ptr ())
    {
	   str += get_Object_R2001_ptr ()->get_key_letter ();
	}
	else if (get_Object_R2001A_ptr ())
	{
		str += get_Object_R2001A_ptr ()->get_key_letter ();
		str += "_A";
	}
	str += "_";
	char buffer[32];
	sprintf (buffer, "%06x",get_object_instance_ID ().get_entire_value ());
	str += buffer;
    appendObjectIdAttributes(str);
}
				



mc_dbms_relationship_m_1_body(I_Object_Instance,m_Attribute_Instance_R2002_coll,I_Attribute_Instance,m_Object_Instance_R2002_ptr);

mc_dbms_relationship_1_m_body(I_Object_Instance,m_Object_R2001_ptr,I_Object,m_Object_Instance_R2001_coll);

mc_dbms_relationship_1_1_body(I_Object_Instance,m_Object_R2001A_ptr,I_Object,m_Object_Instance_R2001A_ptr);

mc_dbms_relationship_m_1_body(I_Object_Instance,m_Related_Object_Instance_Pair_R2010_coll,I_Related_Object_Instance_Pair,m_Object_Instance_R2010_ptr);

mc_dbms_relationship_m_1_body(I_Object_Instance,m_Related_Object_Instance_Pair_R2011_coll,I_Related_Object_Instance_Pair,m_Object_Instance_R2011_ptr);

mc_dbms_relationship_m_1_body(I_Object_Instance,m_SM_Evt_Inst_R2031_coll,I_SM_Evt_Inst,m_Object_Instance_R2031_ptr);

mc_dbms_relationship_m_1_body(I_Object_Instance,m_SM_Evt_Inst_R2032_coll,I_SM_Evt_Inst,m_Object_Instance_R2032_ptr);

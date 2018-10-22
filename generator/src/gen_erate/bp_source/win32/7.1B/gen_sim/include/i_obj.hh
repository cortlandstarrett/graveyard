/*========================================================================
 *
 * File:      $RCSfile: i_obj.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef I_OBJ_HH
#define I_OBJ_HH


#include <u_id.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#include <u_util.hh>


class I_Attribute;
class I_Object_Instance;
class I_Related_Object_Pair;
class I_object_inst_ref_var;
class I_object_inst_ref_set_var;




class I_Object : public SerializableObject
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

    static I_Object*	create (mc_dbms_database* p_db_ptr,
			    const Description& p_key_letter = Description::Default);
    virtual		~I_Object ();

    void		relate_R102 (I_Attribute*);
    void		relate_R102A (I_Attribute*);
    void		relate_R2001 (I_Object_Instance*);
    void		relate_R2001A (I_Object_Instance*);
    void		relate_R2006 (I_Related_Object_Pair*);
    void		relate_R2005 (I_Related_Object_Pair*);


    // Class-extent finds follow
    //
    static I_Object*	find_Object_by_object_ID
			    (mc_dbms_database* p_db_ptr, const Id& p_object_ID);
    static mc_dbms_Set<I_Object*>*
			find_Object_by_key_letter (mc_dbms_database* p_db_ptr,
			    const Description& p_key_letter);


    // Contained collection's finds follow
    //
    I_Attribute*	find_Attribute_R102_by_attribute_ID
			    (const Id& p_attribute_ID) const;

    mc_dbms_Set<I_Attribute*>*
			find_Attribute_R102_by_name
			    (const Description& p_name) const;

    I_Object_Instance*	find_Object_Instance_R2001_by_object_instance_ID
			    (const Id& p_object_instance_ID) const;


    // Return pointers to contained collections
    //
    mc_dbms_List<I_Attribute*>*
			get_Attribute_R102_coll_ptr ()
			    { return (&m_Attribute_R102_coll.getvalue ()); }

    I_Attribute*	get_Attribute_R102A_ptr ()
			    { return m_Attribute_R102A_ptr; }

    mc_dbms_List<I_Object_Instance*>*
			get_Object_Instance_R2001_coll_ptr ()
			    { return (&m_Object_Instance_R2001_coll.getvalue ()); }
    I_Object_Instance* get_Object_Instance_R2001A_ptr ()
			    { return m_Object_Instance_R2001A_ptr; }
    mc_dbms_List<I_Related_Object_Pair*>*
			get_Related_Object_Pair_R2006_coll_ptr ()
			    { return (&m_Related_Object_Pair_R2006_coll.getvalue ()); }
    mc_dbms_List<I_Related_Object_Pair*>*
			get_Related_Object_Pair_R2005_coll_ptr ()
			    { return (&m_Related_Object_Pair_R2005_coll.getvalue ()); }

    static mc_dbms_List<I_Object*>*
			get_class_extent_ptr (mc_dbms_database* p_db_ptr);


    // get/set functions
    //
    const Id&		get_object_ID () const
			    { return m_object_ID; }
    void		set_object_ID (const Id& p_input)
			    { m_object_ID = p_input; }
    const Description&	get_key_letter () const
			    { return m_key_letter; }
    void		set_key_letter (const Description& p_input)
			    { m_key_letter = p_input; }

public:

	long persist() {
		long bytesWritten = 0;

		bytesWritten += writeBlob((char*)&m_object_ID, sizeof(Id));
		bytesWritten += m_key_letter.persist();

		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		return bytesWritten;
	}
	
	void restore() {
		readBlob((char*)&m_object_ID);
		m_key_letter.restore();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}
	
	static char* create() {
		I_Object* inst = new I_Object();
		inst->restore();
		return (char*)inst;
	}

private:
    Id			m_object_ID;
    Description		m_key_letter;

    mc_dbms_relationship_m_1(I_Object,m_Attribute_R102_coll,I_Attribute,m_Object_R102_ptr,mc_dbms_List<I_Attribute*>) m_Attribute_R102_coll;

    mc_dbms_relationship_1_1(I_Object,m_Attribute_R102A_ptr,I_Attribute,m_Object_R102A_ptr,I_Attribute*) m_Attribute_R102A_ptr;

    mc_dbms_relationship_m_1(I_Object,m_Object_Instance_R2001_coll,I_Object_Instance,m_Object_R2001_ptr,mc_dbms_List<I_Object_Instance*>) m_Object_Instance_R2001_coll;

    mc_dbms_relationship_1_1(I_Object,m_Object_Instance_R2001A_ptr,I_Object_Instance,m_Object_R2001A_ptr,I_Object_Instance*) m_Object_Instance_R2001A_ptr;

    mc_dbms_relationship_m_1(I_Object,m_Related_Object_Pair_R2006_coll,I_Related_Object_Pair,m_Object_R2006_ptr,mc_dbms_List<I_Related_Object_Pair*>) m_Related_Object_Pair_R2006_coll;

    mc_dbms_relationship_m_1(I_Object,m_Related_Object_Pair_R2005_coll,I_Related_Object_Pair,m_Object_R2005_ptr,mc_dbms_List<I_Related_Object_Pair*>) m_Related_Object_Pair_R2005_coll;

//    mc_dbms_relationship_m_1(I_Object,m_object_inst_ref_var_coll,I_object_inst_ref_var,m_obj_ptr,mc_dbms_List<I_object_inst_ref_var*>) m_object_inst_ref_var_coll;

//    mc_dbms_relationship_m_1(I_Object,m_object_inst_ref_set_var_coll,I_object_inst_ref_set_var,m_obj_ptr,mc_dbms_List<I_object_inst_ref_set_var*>) m_object_inst_ref_set_var_coll;


    // Helping functions follow
    //
    I_Object (const Description& p_key_letter);
    
    /**
     * This is used only by persistence
     */
    I_Object() { }
};




#endif

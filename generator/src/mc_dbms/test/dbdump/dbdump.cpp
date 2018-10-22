/*========================================================================
 *
 * File:      $RCSfile: dbdump.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:02 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <string>
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>

#include <i_obj.hh>
#include <i_attr.hh>
#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_rel.hh>
#include <i_rop.hh>
#include <u_keyword.hh>
#include <i_var.hh>
#include <i_roip.hh>
#include <u_desc.hh>

using namespace std;

// If running with BP6 then rename the entrypoints to objectstore names
#ifdef BP6

#include <ostore/ostore.hh>
extern os_database* GS_gen_sim_db_ptr;
#define mc_dbms_database os_database
#define mc_dbms_Cursor os_Cursor
#define mc_dbms_List os_List

#else

#include <mc_dbms\mc_dbms.hh>

#endif // BP6

// If this macro is set we'll display actual pointer values if not
// we'll display a 1 to indicate a pointer has a value and 0 to indicate 
// that it's a null pointer.
#if defined(DontDisplayPointers)
const bool DisplayPointers = false;
#else
const bool DisplayPointers = true;
#endif

::ostream& operator<<(::ostream& os, const Id& id )
{
	os << "(" << id.get_class_type()
       << ", " << id.get_entire_value() << ")";
	return os;
}

void dump_Attribute(::ostream* out, const I_Attribute* attr )
{
	*out << "Attribute (" << (DisplayPointers ? attr : (bool)attr) << ") Name = " << attr->get_name().char_ptr()
		  << "\n\t" << "Id = " << attr->get_attribute_ID ()
		  << "\n\t" << "CDT = " << attr->get_core_data_type ()
		  << "\n\t" << "UDT = " << attr->get_user_data_type ()
		  << "\n\t" << "is_ref = " << attr->get_is_referential_attr ()
		  << "\n\t" << "is_id = " << attr->get_is_identifier_attr ()
		  << "\n\t" << "is_primary_id = " << attr->get_is_primary_identifier_attr ()
		  << "\n\t" << "uid_max = " << attr->get_highest_unique_id_value ()
		  << "\n\t";
}

void dump_data(char* fileName = 0, const Description& desc = "")
{
	::ostream*  out = &cout;
	if (fileName) {
		out = new ::ofstream(fileName, ios_base::app);
	}
	
	*out << "\n\n"
		<< "dump_data() started: " << desc.char_ptr()
		<< "\n\n";

#ifdef BP6
        os_database* p_db_ptr = GS_gen_sim_db_ptr;
#else
        mc_dbms_database* p_db_ptr = mc_dbms_database::get_persistent_database();
#endif
        mc_dbms_Cursor< I_Object * > objCursor(*(I_Object::get_class_extent_ptr(p_db_ptr)));
        ;
		for (I_Object* objPtr = objCursor.first(); objPtr ; objPtr = objCursor.next () )
		{
			*out << "Object (" << (DisplayPointers ? objPtr : (bool)objPtr) << ") " 
                << " Id = " << objPtr->get_object_ID ()
				    << " KL = " << objPtr->get_key_letter ().char_ptr() << endl;

            mc_dbms_Cursor< I_Attribute* > attrCursor(*(objPtr->get_Attribute_R102_coll_ptr()));
			for ( I_Attribute* attrPtr = attrCursor.first(); attrPtr ; attrPtr = attrCursor.next() )
			{
				dump_Attribute(out, attrPtr );
			}
            
            mc_dbms_Cursor< I_Object_Instance* > oinstCursor(*(objPtr->get_Object_Instance_R2001_coll_ptr()));
			for ( I_Object_Instance* oinstPtr = oinstCursor.first(); oinstPtr; oinstPtr = oinstCursor.next() )
			{
                *out << "Object Instance (" << (DisplayPointers ? oinstPtr : (bool)oinstPtr) << ") "
                    << " Id = " << oinstPtr->get_object_instance_ID ()
				    << " related = " << oinstPtr->get_related_flag ()
				    << " obj_ptr = " << (DisplayPointers ? oinstPtr->get_Object_R2001_ptr() : (bool)oinstPtr->get_Object_R2001_ptr())
					<< endl;
                mc_dbms_Cursor< I_Attribute_Instance* > ainstCursor(*(oinstPtr->get_Attribute_Instance_R2002_coll_ptr()));
				for ( I_Attribute_Instance* ainstPtr = ainstCursor.first(); ainstPtr; ainstPtr = ainstCursor.next() )
				{
				*out << "Attribute Instance (" << (DisplayPointers ? ainstPtr : (bool)ainstPtr) << ") "
                    << " Id = " << ainstPtr->get_attribute_ID()
					<<	" oinst_ptr = " << (DisplayPointers ? ainstPtr->get_Object_Instance_R2002_ptr() : (bool)ainstPtr->get_Object_Instance_R2002_ptr()) 
					<<	" attr_ptr = " << (DisplayPointers ? ainstPtr->get_Attribute_R2002_ptr () : (bool)ainstPtr->get_Attribute_R2002_ptr ()) 
					<<	" var_ptr = " << (DisplayPointers ? ainstPtr->get_var_ptr() : (bool)ainstPtr->get_var_ptr()) 
					<<	" value = " << ainstPtr->get_var_ptr()->get_value_str().char_ptr() 
					<<	endl;
				}
				

                mc_dbms_Cursor< I_Related_Object_Instance_Pair* > roipCursor(*(oinstPtr->get_Related_Object_Instance_Pair_R2010_coll_ptr()));
				for ( I_Related_Object_Instance_Pair* roipPtr = roipCursor.first(); roipPtr; roipPtr = roipCursor.next() )
				{
				*out << "ROIP R2010 Instance (" << (DisplayPointers ? roipPtr : (bool)roipPtr) << ") "
                    << " Id = " << roipPtr->get_relationship_ID()
					<<	" oinst_ptr = " << (DisplayPointers ? roipPtr->get_Object_Instance_R2010_ptr() : (bool)roipPtr->get_Object_Instance_R2010_ptr()) 
					<<	" audited = " << roipPtr->get_R2010_is_audited()
					<<  " equalIDs = " << roipPtr->get_num_with_equal_ids()
					<<  " Rnum = " << roipPtr->get_Rnum_str().char_ptr()
					<<	endl;
				}

                mc_dbms_Cursor< I_Related_Object_Instance_Pair* > roipCursor2(*(oinstPtr->get_Related_Object_Instance_Pair_R2011_coll_ptr()));
				for ( I_Related_Object_Instance_Pair* roipPtr2 = roipCursor2.first(); roipPtr2; roipPtr2 = roipCursor2.next() )
				{
				*out << "ROIP R2011 Instance (" << (DisplayPointers ? roipPtr2 : (bool)roipPtr2) << ") "
                    << " Id = " << roipPtr2->get_relationship_ID()
					<<	" oinst_ptr = " << (DisplayPointers ? roipPtr2->get_Object_Instance_R2011_ptr() : (bool)roipPtr2->get_Object_Instance_R2011_ptr()) 
					<<	" audited = " << roipPtr2->get_R2011_is_audited()
					<<  " equalIDs = " << roipPtr2->get_num_with_equal_ids()
					<<  " Rnum = " << roipPtr2->get_Rnum_str().char_ptr()
					<<	endl;
				}

			}
		}

        mc_dbms_Cursor< I_Relationship* > relCursor(*(I_Relationship::get_class_extent_ptr(p_db_ptr)));
		for ( I_Relationship* relPtr = relCursor.first(); relPtr; relPtr = relCursor.next() )
		{
			*out 
                << "Relationship Id = " << relPtr->get_relationship_ID ()
                << " Relationship Number = " << relPtr->get_number ().char_ptr()
                << endl;
            mc_dbms_Cursor< I_Related_Object_Pair* > ropCursor(*(relPtr->get_Related_Object_Pair_R2003_coll_ptr()));
			for ( I_Related_Object_Pair* ropPtr = ropCursor.first(); ropPtr; ropPtr = ropCursor.next() )
			{
				*out << "ROP ONE Cond = " << ropPtr->get_ONE_side_is_conditional ()
				  << " ONE Many = " << ropPtr->get_ONE_side_is_many ()
				  << " ONE Phrase = " << ropPtr->get_ONE_side_phrase ().char_ptr()
				  << " OTH Cond = " << ropPtr->get_OTH_side_is_conditional ()
				  << " OTH Many = " << ropPtr->get_OTH_side_is_many ()
				  << " OTH Phrase = " << ropPtr->get_OTH_side_phrase ().char_ptr()
				  << " ID Obj = " << ropPtr->get_Object_R2005_ptr ()->get_key_letter ().char_ptr()
				  << " REF Obj = " << ropPtr->get_Object_R2006_ptr ()->get_key_letter ().char_ptr()
				  << endl;
			}
		}

		mc_dbms_Cursor< I_Object_Instance* > oinstCursor1(*(I_Object_Instance::get_class_extent_ptr(p_db_ptr)));
		for ( I_Object_Instance* oinstPtr1 = oinstCursor1.first(); oinstPtr1; oinstPtr1 = oinstCursor1.next())
		{
                *out << "Object Instance (" << (DisplayPointers ? oinstPtr1 : (bool)oinstPtr1) << ") "
                    << " Id = " << oinstPtr1->get_object_instance_ID ()
				    << " related = " << oinstPtr1->get_related_flag ()
				    << " obj_ptr = " << (DisplayPointers ? oinstPtr1->get_Object_R2001_ptr() : (bool)oinstPtr1->get_Object_R2001_ptr())
					<< endl;
		}
}


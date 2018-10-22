#include <mc_dbms/external_object.h>
#include <i_var.hh>
#include <i_ainst.hh>
#include <i_ir_rop.hh>
#include <i_c_rop.hh>
#include <i_rel.hh>
#include <i_obj.hh>
#include <i_attr.hh>
#include <i_roip.hh>

#include <exception>

char* mcdbms_RestoreExternalObject(TrackedType typeID)
{
	char* newInstance = 0;
	
	switch (typeID) {
	case tt_I_frag_ref_var:
		newInstance = (char*)I_frag_ref_var::create();
		break;
	case tt_I_timer_inst_ref_var:
		newInstance = (char*)I_timer_inst_ref_var::create();
		break;
	case tt_I_mapping_inst_ref_var:
		newInstance = (char*)I_mapping_inst_ref_var::create();
		break;
	case tt_I_date_var:
		newInstance = (char*)I_date_var::create();
		break;
	case tt_I_timestamp_var:
		newInstance = (char*)I_timestamp_var::create();
		break;
	case tt_I_mapping_inst_var:
		newInstance = (char*)I_mapping_inst_var::create();
		break;
	case tt_I_event_inst_var:
		newInstance = (char*)I_event_inst_var::create();
		break;
	case tt_I_object_inst_ref_var:
		newInstance = (char*)I_object_inst_ref_var::create();
		break;
	case tt_I_object_inst_ref_set_var:
		newInstance = (char*)I_object_inst_ref_set_var::create();
		break;
	case tt_I_current_state_var:
		newInstance = (char*)I_current_state_var::create();
		break;
	case tt_I_unique_id_var:
		newInstance = (char*)I_unique_id_var::create();
		break;
	case tt_I_string_var:
		newInstance = (char*)I_string_var::create();
		break;
	case tt_I_real_var:
		newInstance = (char*)I_real_var::create();
		break;
	case tt_I_integer_var:
		newInstance = (char*)I_integer_var::create();
		break;
	case tt_I_boolean_var:
		newInstance = (char*)I_boolean_var::create();
		break;
	case tt_I_enumerator_var:
		newInstance = (char*)I_enumerator_var::create();
		break;
	case tt_I_void_var:
		newInstance = (char*)I_void_var::create();
		break;
		
	case tt_I_Attribute_Instance:
		newInstance = (char*)I_Attribute_Instance::create();
		break;
	case tt_I_ID_REF_Rel_Obj_Pair:
		newInstance = (char*)I_ID_REF_Rel_Obj_Pair::create();
		break;
	case tt_I_Chain_Rel_Obj_Pair:
		newInstance = (char*)I_Chain_Rel_Obj_Pair::create();
		break;

		
	case tt_I_Relationship:
		newInstance = (char*)I_Relationship::create();
		break;
	case tt_I_Object:
		newInstance = (char*)I_Object::create();
		break;
	case tt_I_Attribute:
		newInstance = (char*)I_Attribute::create();
		break;
	case tt_I_Related_Object_Instance_Pair:
		newInstance = (char*)I_Related_Object_Instance_Pair::create();
		break;
		
	default:
		throw std::runtime_error("Unexpected type identifier in mcdbms_RestoreExternalObject()");
	};
	
	return newInstance;
}

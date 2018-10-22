.//----------------------------------------------------------------------------
.//
.function fx_get_base_arch_prefix_name
  .assign attr_result = "MC3020"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_default_arch_prefix_name
  .assign attr_result = "Escher"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_facade_file_name
.param inst_ref te_c .// component
  .assign attr_result = "${te_c.Name}_domainfacade"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_copyright_notice
  .assign attr_result = "COPYRIGHT"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_dispatcher_name
.param inst_ref te_c
  .assign attr_result = "${te_c.Name}_DomainDispatcher"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_mech_file_name
.param inst_ref te_c
  .assign attr_result = "${te_c.Name}_mechs"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_init_file_name
.param inst_ref te_c
  .assign attr_result = "${te_c.Name}_dom_init"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_classes_file_name
.param inst_ref te_c
  .assign attr_result = "${te_c.Name}_classes"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_domain_enums_file_name
.param inst_ref te_c
  .assign attr_result = "${te_c.Name}_enums"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_sys_mech_file_name
  .assign attr_result = "sys_mechs"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_sys_types_file_name
  .assign attr_result = "sys_types"
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_object_extent_size
.param inst_ref te_class
  .assign attr_result = false
  .assign attr_max_size_value = ""
  .assign attr_include_file = ""
  .if ( "$r{te_class.InstanceMaxNo}" != "" )
      .assign attr_max_size_value = "$r{te_class.InstanceMaxNo}"
      .assign attr_include_file = "$r{te_class.InstanceMaxNoDefIncludeFile}"
      .assign attr_result = true
  .end if
.end function
.//
.//----------------------------------------------------------------------------
.//
.// O_OBJ�Ɋ֘A�Â��Ă���ŏ���O_ATTR���擾����B
.function fx_get_first_attribute_in_object_model
.param inst_ref te_class
  .select any obj from instances of O_OBJ where (selected.Obj_ID == te_class.Obj_ID)
  .//.if (empty obj)
  .//.print "++++ O_OBJ not found. ${te_class.Name}"
  .//.else
  .//.print "++++ O_OBJ found!. ${te_class.Name}"
  .//.end if
  .select any attr_result related by obj->O_ATTR[R102] where (selected.PAttr_ID == 0)
  .select many obj_attr_set related by obj->O_ATTR[R102]
  .for each obj_attr in obj_attr_set
    .select one previous_attr related by obj_attr->O_ATTR[R103.'precedes']
    .if ( empty previous_attr )
      .assign attr_result = obj_attr
      .break for
    .end if
  .end for
.end function
.//
.//----------------------------------------------------------------------------
.//
.// code��������attribute���ǂ����𔻒肷��B
.// ����ŗǂ������M�Ȃ��c
.function fx_generate_code_for_object_attribute
.param inst_ref obj_attr
  .assign attr_result = TRUE
  .select one te_dt related by obj_attr->S_DT[R114]->TE_DT[R2021]
  .select one te_attr related by obj_attr->TE_ATTR[R2033]
  .//
  .// "current_state" attribute.
  .if (te_dt.Core_Typ == 6)
    .assign attr_result = FALSE
  .else
    .if (te_attr.translate == FALSE)
      .assign attr_result = FALSE
    .end if
  .end if
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_auto_inc_get_llimit_value_macro_name
.param inst_ref te_attr
  .select one o_obj related by te_attr->TE_CLASS[R2061]->O_OBJ[R2019]
  .invoke namespace = GetDomainObjectNamespace(o_obj)
  .assign attr_result = "${namespace.result}_AUTOINC_LOWER_LIMIT"
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_auto_inc_get_hlimit_value_macro_name
.param inst_ref te_attr
  .select one o_obj related by te_attr->TE_CLASS[R2061]->O_OBJ[R2019]
  .invoke namespace = GetDomainObjectNamespace(o_obj)
  .assign attr_result = "${namespace.result}_AUTOINC_HIGHER_LIMIT"
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_auto_inc_get_new_value_macro_name
.param inst_ref te_attr
  .select one o_obj related by te_attr->TE_CLASS[R2061]->O_OBJ[R2019]
  .invoke namespace = GetDomainObjectNamespace(o_obj)
  .assign attr_result = "${namespace.result}_AUTOINC_GetNewValue"
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_auto_inc_id_mgmt_variable_name
.param inst_ref te_attr
  .select one o_obj related by te_attr->TE_CLASS[R2061]->O_OBJ[R2019]
  .invoke namespace = GetDomainObjectNamespace(o_obj)
  .assign attr_result = "${namespace.result}_AUTOINC_currentId"
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_get_bridge_extend_name_prefix
.param inst_ref te_ee
  .select any te_c related by te_ee->TE_C[R2085]
  .assign attr_result = "${te_c.Name}_BridgeExtend_${te_ee.Key_Lett}"
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_is_exist_real_func
.param inst_ref te_ee
  .assign attr_result = FALSE
  .select any te_brg related by te_ee->S_EE[R2020]->S_BRG[R19]->TE_BRG[R2025] where ( selected.IsRealFunc == TRUE )
  .if (not_empty te_brg)
    .assign attr_result = TRUE
  .end if
.end function  
.//
.//----------------------------------------------------------------------------
.//
.function fx_generate_auto_inc_id_execution
.param inst_ref te_attr
  .assign attr_result = false
  .if (te_attr.isAutoInc)
    .assign attr_result = true
    .invoke llimit_macro_name = fx_get_auto_inc_get_llimit_value_macro_name(te_attr)
    .invoke hlimit_macro_name = fx_get_auto_inc_get_hlimit_value_macro_name(te_attr)
    .invoke get_macro_name = fx_get_auto_inc_get_new_value_macro_name(te_attr)
    .invoke var_name = fx_get_auto_inc_id_mgmt_variable_name(te_attr)
  /* FX Extention : AUTOINC Coloring */
  /* setup value of ${te_attr.Name} */
  self->${te_attr.GeneratedName} = ${get_macro_name.result}(${var_name.result});
  .end if
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_generate_auto_inc_id_definision
.param inst_ref te_attr
.param boolean gen_decl
  .assign attr_result = false
  .if (te_attr.isAutoInc)
    .assign attr_result = true
    .invoke llimit_macro_name = fx_get_auto_inc_get_llimit_value_macro_name(te_attr)
    .invoke hlimit_macro_name = fx_get_auto_inc_get_hlimit_value_macro_name(te_attr)
    .invoke get_macro_name = fx_get_auto_inc_get_new_value_macro_name(te_attr)
    .if (gen_decl)
/* auto inclemental id's Lower Limit */
#define ${llimit_macro_name.result} ${te_attr.AutoIncLowLimit}
/* auto inclemental id's Higher Limit */
#define ${hlimit_macro_name.result} ${te_attr.AutoIncHighLimit}
/* auto inclemental value getter */
#define ${get_macro_name.result}(x)    \
        .if (te_attr.AutoDirection == "UP")
((x)=((++(x)-${llimit_macro_name.result})%(${hlimit_macro_name.result}-${llimit_macro_name.result}+1)+${llimit_macro_name.result}))
	.else
((x)=((${hlimit_macro_name.result}-(--(x)))%(${hlimit_macro_name.result}-${llimit_macro_name.result}+1)+${hlimit_macro_name.result}))
	.end if
    .else
/* auto inclemental value for unique_id */
        .invoke var_name = fx_get_auto_inc_id_mgmt_variable_name(te_attr)
static int ${var_name.result} = \
        .if (te_attr.AutoDirection == "UP")
${llimit_macro_name.result} - 1\
        .else
${llimit_macro_name.result} + 1\
	.end if
;
    .end if
  .end if
.end function
.//
.//----------------------------------------------------------------------------
.//
.function fx_setup_subsystem_init
  .select many objs from instances of O_OBJ
  .// �t���O�̏������Ȃ�
  .for each obj in objs
    .assign obj.IsExcludeFromGen = false
  .end for
.//    .select many ep_pkgs from instances of EP_PKG
.//    .for each ep_pkg in ep_pkgs
.//      .select many objs related by ep_pkg->PE_PE[R8000]->O_OBJ[R8001]
.//      .for each obj in objs
.//          .// �t���O�̏������Ȃ�
.//	  .assign obj.IsExcludeFromGen = false
.//
.//          .// Initialize Object���ǂ����𔻒f���A�t���O���Z�b�g����B
.//	  .if ( "${obj.Name}" == "${ep_pkg.Name} init" )
.//	    .assign obj.IsInitObject = true
.//	  .else
.//	    .assign obj.IsInitObject = false
.//	  .end if
.//      .end for
.//    .end for
.end function
.//
.//----------------------------------------------------------------------------
.// Initialize Object��set���擾����
.//.function fx_get_initialize_object_set
.//  .select many attr_obj_set from instances of O_OBJ where (selected.IsInitObject == true)
.//.end function
.//
.//
.//============================================================================
.// �ȉ���mark�t�@�C���Ŏw�肳���function
.//----------------------------------------------------------------------------
.// ���ɂ����Ɏ����B�ꏊ�͂��Ƃōl����B
.function SetDomainEventMaxNumber
.param string domainName
.param integer maxInternalEventNo
.param integer maxExternalEventNo
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .assign msg = ""
  .if (not_empty te_c)
      .assign te_c.MaxInternalEvents = maxInternalEventNo
      .assign te_c.MaxExternalEvents = maxExternalEventNo 
      .assign msg = "set maxEventNo to ${maxInternalEventNo} + ${maxExternalEventNo} "
  .else
      .assign msg = "ERROR: Component ${domainName} not found.\n => SetDomainEventMaxNumber()"
  .end if
  .print "${msg}"
.end function
.//
.//-----------------------------------------------------------------------------
.//
.function SetDomainRelationExtentMaxNumber
.param string domainName
.param integer maxRelationExtents
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .if (not_empty te_c)
      .assign te_c.MaxRelationExtents = maxRelationExtents
      .print "set maxRelationExtens to ${maxRelationExtents}"
  .else
      .print "ERROR: Component ${domainName} not found.\n => SetDomainRelationExtentMaxNumber()"
  .end if
.end function
.//
.//-----------------------------------------------------------------------------
.//
.function SetDomainSelectionNodeMaxNumber
.param string domainName
.param integer maxSelectionNode
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .if (not_empty te_c)
      .assign te_c.MaxSelectionNodeExtents = maxRelationNode
  .else
      .print "ERROR: Component ${domainName} not found.\n => SetDomainSelectionNodeMaxNumber()"
  .end if
.end function
.//
.//-----------------------------------------------------------------------------
.//
.function TagUseFacadeMaxDef
.param string domainName
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .if (not_empty te_c)
      .assign te_c.isUseFacadeMaxDef = true
  .else
      .print "ERROR: Component ${domainName} not found.\n => SetDomainRelationExtentMaxNumber()"
  .end if
.end function
.//
.//-----------------------------------------------------------------------------
.//
.function SetDomainFacadeMutexLockUse
.param string domainName
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .if (not_empty te_c)
      .assign te_c.isUseMutexLock = true
  .else
      .print "ERROR: Component ${domainName} not found.\n => SetDomainFacadeMutexLockUse()"
  .end if
.end function
.//
.//-----------------------------------------------------------------------------
.//
.function mark_obj_as_fixed_inst_no_extend
.param string domainName
.param string className
.param string instanceMaxStr
.param string includeFile
  .select any te_c from instances of TE_C where (selected.Name == domainName)
  .if (not_empty te_c)
    .select any te_class related by te_c->TE_CLASS[R2064] where (selected.Key_Lett == className)
    .if (not_empty te_class)
      .assign te_class.InstanceMaxNo = instanceMaxStr
      .assign te_class.InstanceMaxNoDefIncludeFile = includeFile
    .else
      .print "ERROR: Class ${className} not found.\n => mark_obj_as_fixed_inst_no_extend()"
    .end if
  .else
      .print "ERROR: Component ${domainName} not found.\n => mark_obj_as_fixed_inst_no_extend()"
  .end if
.end function
.//

.//============================================================================
.// 
.// Domain Facade Implementation
.//
.//============================================================================
.function fx_generate_domain_facade_file_prologue
.param inst_ref te_c
.param boolean p_gen_decl
    .invoke file_name = fx_get_domain_facade_file_name(te_c)
    .select any te_file from instances of TE_FILE;
    .select any te_sys from instances of TE_SYS;
/******************************************************************************
    .if (p_gen_decl) .// header file
 * File: ${file_name.result}.${te_file.hdr_file_ext}
    .else
 * File: ${file_name.result}.${te_file.src_file_ext}
    .end if
 *
 * Domain: ${te_c.Name}
 * Project: ${te_sys.Name}
 *
    .invoke copyright = fx_get_copyright_notice()
 *
 *****************************************************************************/

    .if (p_gen_decl )
#ifndef _$ur{file_name.result}_${te_file.hdr_file_ext}_
#define _$ur{file_name.result}_${te_file.hdr_file_ext}_

    .end if
    .//
.end function
.//
.//
.function fx_generate_domain_facade_file_epilogue
.param inst_ref te_c
.param boolean p_gen_decl
    .//
    .if (p_gen_decl )
    .invoke file_name = fx_get_domain_facade_file_name(te_c)
    .select any te_file from instances of TE_FILE;
#endif /* _$ur{file_name.result}_${te_file.hdr_file_ext}_ */
    .end if
    .//
.end function
.//
.print "======= te_file.hdr_file_ext: ${te_file.hdr_file_ext}";
.print "======= te_file.sys_main: ${te_file.sys_main}";
.print "======= te_sys.Name: ${te_sys.Name}";
.print "======= te_sys.self_name: ${te_sys.self_name}";
.select many te_cis from instances of TE_CI;
.for each te_ci in te_cis 
.print "======= te_ci.Name: ${te_ci.Name}";
.end for
.select any te_c from instances of TE_C
.print "======= MaxSelfEvents: ${te_c.MaxSelfEvents}";
.print "======= MaxNonSelfEvents: ${te_c.MaxNonSelfEvents}";
.select many te_cs from instances of TE_C;
.for each te_c in te_cs 
.print "======= te_c.Name: ${te_c.Name}";
.invoke file_name = fx_get_domain_facade_file_name(te_c)
.print "======= domain_facade_name: ${file_name.result}";
.end for
.//
.//============================================================================
.//
.function fx_generate_domain_facade_declaration_body
.param inst_ref te_c
    .//
    .invoke base_arch_prefix = fx_get_base_arch_prefix_name()
    .select any te_file from instances of TE_FILE;
    .assign domainName = te_c.Name
    .//
void ${domainName}_DomainFacade_Initialize(
    ${base_arch_prefix.result}_waitForExternalEvents_Fp waitForExtEventFp,
    ${base_arch_prefix.result}_callOutFp eventEmptyCalloutFP,
    ${base_arch_prefix.result}_callOutFp nodeEmptyCalloutFP,
    ${base_arch_prefix.result}_callOutFp timerEmptyCalloutFP /* dummy */
);

.end function
.//
.//============================================================================
.//
.function fx_generate_domain_facade_definition_body
.param inst_ref te_c
    .//
    .invoke base_arch_prefix = fx_get_base_arch_prefix_name()
    .assign IsUseFacadeMaxSizeDef = false
    .assign domainName = te_c.Name

/* Domain Facade Database variable reference */
extern ${base_arch_prefix.result}_domainInfo_t ${domainName}_domainExecInfo;

/* Domain Event Database definifion */
static ${base_arch_prefix.result}_eventDB_t ${domainName}_domainEventDB;
/* Domain Object Node Database definifion */
static ${base_arch_prefix.result}_objNodeDB_t ${domainName}_domainObjNodeDB;

union ${domainName}_xtUMLEvents_u
{
    Escher_xtUMLEvent_t mc_event_base;
    ${domainName}_DomainEvents_u mc_events_in_domain_${domainName};
}
typedef union ${domainName}_xtUMLEvents_u ${domainName}_xtUMLEvents_u

void ${domainName}_DomainFacade_Initialize(
    ${base_arch_prefix.result}_waitForExternalEvents_Fp waitForExtEventFp,
    ${base_arch_prefix.result}_callOutFp eventEmptyCalloutFP,
    ${base_arch_prefix.result}_callOutFp nodeEmptyCalloutFP,
    ${base_arch_prefix.result}_callOutFp timerEmptyCalloutFP /* dummy */
)
{
    ${domainName}_domainExecInfo.eventDB = &${domainName}_domainEventDB;
    ${domainName}_domainExecInfo.objNodeDB = &${domainName}_domainObjNodeEventDB;

    ${base_arch_prefix.result}_DomainDB_Initialize(
	    &${domainName}_domainExecInfo,
	    sizeof(${domainName}_xtUMLEvents_u),	/* event size */
    .if ( te_c.isUseFacadeMaxDef )
            .assign event_max_no = "${domainName}_INTERNAL_EVENT_MAX_NO"
	    ${event_max_no},	/* max number of event */
	    .assign obj_collection = "${domainName}_SELECTNODE_MAX_NO + ${domainName}_RELNODE_MAX_NO"
	    ${obj_collection},  /* max number of objekct node */

    .else
            .assign event_max_no = te_c.MaxInternalEvents + te_c.MaxExternalEvents
	    ${event_max_no},	/* max number of event */
	    .// MaxSelectionNodeExtentsが0ならデフォルト値(100)にする
	    .if (te_c.MaxSelectionNodeExtents == 0) 
	        .assign te_c.MaxSelectionNodeExtents = 100
	    .end if
	    .assign obj_collection = te_c.MaxRelationExtents + te_c.MaxSelectionNodeExtents
	    ${obj_collection},  /* max number of object node */
    .end if
    	    .// interleavedBridgeはとりあえず0固定
	    .assign interleavedBridge = 0
	    ${interleavedBridge}, /* interleaved bridge max no */
	    ${te_c.isUseMutexLock}, /* true=>use, false=>no use */
	    .invoke domainDispatcherName = fx_get_domain_dispatcher_name(te_c)
	    ${domainDispatcherName.result}, /* domain event dispatcher */
	    waitForExtEventFp,
	    eventEmptyCalloutFP,
	    nodeEmptyCalloutFP
    );

    /* Initialize Domain OOA Model */
    InitializeDomain_${domainName}();

    /* Initialize SubSystem */
    ${domainName}_execute_initialization();

}

void ${domainName}_DomainFacade_Execute(${base_arch_prefix.result}_threadInfo_t* thread)
{
    ${base_arch_prefix.result}_startDispatch(thread, &${domainName}_domainExecInfo);
}
.end function
.//
.// main
.select any te_c from instances of TE_C;
.// header file
.invoke prologue = fx_generate_domain_facade_file_prologue(te_c, true)
.invoke epilogue = fx_generate_domain_facade_file_epilogue(te_c, true)
.invoke decl_code = fx_generate_domain_facade_declaration_body(te_c)
.//
${prologue.body}
.invoke file_name = fx_get_domain_classes_file_name(te_c)
#include "${file_name.result}.${te_file.hdr_file_ext}"

${decl_code.body}

${epilogue.body}
.//
.invoke file_name = fx_get_domain_facade_file_name(te_c)
.emit to file "${te_file.system_source_path}/${file_name.result}.${te_file.hdr_file_ext}"
.//
.// source file
.invoke prologue = fx_generate_domain_facade_file_prologue(te_c, false)
.invoke epilogue = fx_generate_domain_facade_file_epilogue(te_c, false)
.invoke defn_code = fx_generate_domain_facade_definition_body(te_c)
.//
${prologue.body}

.invoke file_name = fx_get_domain_mech_file_name(te_c)
#include "${file_name.result}.${te_file.hdr_file_ext}"
.invoke file_name = fx_get_domain_init_file_name(te_c)
#include "${file_name.result}.${te_file.hdr_file_ext}"
.invoke file_name = fx_get_domain_facade_file_name(te_c)
#include "${file_name.result}.${te_file.hdr_file_ext}"
.invoke file_name = fx_get_domain_classes_file_name(te_c)
#include "${file_name.result}.${te_file.hdr_file_ext}"

${defn_code.body}

${epilogue.body}
.invoke file_name = fx_get_domain_facade_file_name(te_c)
.emit to file "${te_file.system_source_path}/${file_name.result}.${te_file.src_file_ext}"

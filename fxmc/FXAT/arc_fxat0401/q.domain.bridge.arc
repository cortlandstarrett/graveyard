.//============================================================================
.// $RCSfile: q.domain.bridge.arc,v $
.//
.// Description:
.// External Entity bridge process skeleton generator.
.//
.// Notice:
.// (C) Copyright 1998-2013 Mentor Graphics Corporation
.//     All rights reserved.
.//
.// This document contains confidential and proprietary information and
.// property of Mentor Graphics Corp.  No part of this document may be
.// reproduced without the express written permission of Mentor Graphics Corp.
.//============================================================================
.//
.//
.//============================================================================
.// Include only the class header files that we access!
.//============================================================================
.function AddBridgeIncludeFiles
  .param inst_ref te_sys
  .param inst_ref te_ee
  .param boolean gen_declaration
  .//
  .select any te_eq from instances of TE_EQ
  .select any te_file from instances of TE_FILE
  .select any te_target from instances of TE_TARGET
.//-- 010:20140307 Modified Start (nomura)
  .select one te_c related by te_ee->TE_C[R2085]
  .invoke domain_mech = fx_get_domain_mech_file_name(te_c)
#include "${domain_mech.result}.${te_file.hdr_file_ext}"
#include "${te_ee.Include_File}"
.//#include "${te_file.types}.${te_file.hdr_file_ext}"
.//-- 010:20140307 Modified End (nomura)
  .if ( not gen_declaration )
    .if ( te_sys.PersistentClassCount > 0 )
      .if ( te_ee.Key_Lett == "PERSIST" )
        .select any te_brg related by te_ee->S_EE[R2025]->S_BRG[R19] where ( selected.Name == "commit" )
        .if ( not_empty te_brg )
#include "${te_file.persist}.${te_file.hdr_file_ext}"
        .end if
      .elif ( te_ee.Key_Lett == "NVS" )
#include "${te_file.nvs}.${te_file.hdr_file_ext}"
      .end if
    .end if
    .if ( ( "ARCH" == te_ee.Key_Lett ) and ( "C" == te_target.language ) )
extern bool ${te_eq.run_flag}; /* Turn this false to stop the event queues.  */
    .end if
  .end if
.end function
.//
.//============================================================================
.// Build the include file body for the bridge.
.//============================================================================
.function TE_BRG_CreateDeclarations
  .param inst_ref te_ee
  .param inst_ref_set te_brgs
  .select any te_file from instances of TE_FILE
  .select any te_target from instances of TE_TARGET
  .for each te_brg in te_brgs
    .if ( first te_brgs )
      .if ( "C++" == te_target.language )
class ${te_ee.RegisteredName} {
  public:
      .end if
    .end if
    .select one te_aba related by te_brg->TE_ABA[R2010]
    .if ( "C++" == te_target.language )
      .include "${te_file.arc_path}/t.ee.bridge.h"
      .if ( last te_brgs )
};
      .end if
    .else
      .include "${te_file.arc_path}/t.component.message.h"
    .end if
  .end for
.end function
.//
.//============================================================================
.// Generate the bridge skeletons.  Go ahead and translate any action
.// language in the body of the bridge.
.// For TIM, NVS and PERSIST do some special processing.
.//============================================================================
.function TE_BRG_CreateDefinition
  .param inst_ref te_sys
  .param inst_ref te_ee
  .param inst_ref_set te_brgs
  .select any te_eq from instances of TE_EQ
  .select any te_file from instances of TE_FILE
  .select any te_instance from instances of TE_INSTANCE
  .select any te_prefix from instances of TE_PREFIX
  .select any te_target from instances of TE_TARGET
  .assign statement_trace = false
  .select one te_c related by te_ee->TE_C[R2085]
  .if ( not_empty te_c )
    .assign statement_trace = te_c.StmtTrace
  .end if
  .for each te_brg in te_brgs
    .select one te_aba related by te_brg->TE_ABA[R2010]
    .select one te_dt related by te_brg->S_BRG[R2025]->S_DT[R20]->TE_DT[R2021]
    .select one s_brg related by te_brg->S_BRG[R2025]
    .include "${te_file.arc_path}/t.ee.brg.c"
  .end for
.end function
.//

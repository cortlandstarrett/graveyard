.//============================================================================
.// Notice:
.// (C) Copyright 1998-2013 Mentor Graphics Corporation
.//     All rights reserved.
.//
.// This document contains confidential and proprietary information and
.// property of Mentor Graphics Corp.  No part of this document may be
.// reproduced without the express written permission of Mentor Graphics Corp.
.//============================================================================
.//
.//-- 018:20140320 Add Start (saitou)
.//  �ߋ�BP�Ƃ̌݊����̂��߂ɁA�Ō�Ƀ_�~�[������ǉ�����(isCalledByExt�̑���)�B
.//  void �����̏ꍇ�͈����������Ƃ������ƂȂ̂ŁA��菜���Ă���
.//  �������֐��Ƃ���Mark����Ă���ꍇ�́A�ΏۊO�Ƃ���B
.if ( te_sync.IsInitFunction != TRUE )
  .if ( "$r{te_aba.ParameterDeclaration}" == "void" )
    .assign te_aba.ParameterDeclaration = ""
  .end if
  .if ( "$r{te_aba.ParameterDeclaration}" != "" )
    .assign te_aba.ParameterDeclaration = te_aba.ParameterDeclaration + ","
  .end if
  .assign te_aba.ParameterDeclaration = te_aba.ParameterDeclaration + " int dummy "
.end if
.//-- 018:20140320 Add Start (saitou)
.if ( te_sync.IsSafeForInterrupts )
void ${te_sync.intraface_method}(${te_aba.ParameterDeclaration});
.end if
${te_aba.ReturnDataType} ${te_aba.GeneratedName}(${te_aba.ParameterDeclaration});
.//

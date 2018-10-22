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

  /*
   * Array of string names of the state machine names.
   * Index is the (MC enumerated) number of the state.
   */
.//-- 016: 20140305 Modified Start (saitou) 
  static const char * const ${te_sm.state_names_array}[ ${state_space} ] = {
.//-- 016: 20140305 Modified End (saitou) 
    .// Element zero is unused.
    "",
${state_names}\
  };

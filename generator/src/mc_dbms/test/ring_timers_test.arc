.//=======================================================================
.//
.// File:      $RCSfile: ring_timers_test.arc,v $
.// Version:   $Revision: 1.9 $
.// Modified:  $Date: 2013/01/10 23:41:40 $
.//
.// (c) Copyright 2005-2013 by Mentor Graphics Corp.  All rights reserved.
.//
.//=======================================================================
.// This document contains information proprietary and confidential to
.// Mentor Graphics Corp., and is not for external distribution.
.//=======================================================================
.//
.// This is a comment
Beginning of current_states
.select many monkeys from instances of M
.for each monkey in monkeys
  current_state is ${monkey.current_state}
.print "${monkey.current_state}"
.end for
End of List of current_states
.emit to file "ring_timers.txt"


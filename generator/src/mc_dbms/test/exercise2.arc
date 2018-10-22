.//=======================================================================
.//
.// File:      $RCSfile: exercise2.arc,v $
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
Beginning of List of Object Names
.select many class_set from instances of O_OBJ
.for each obj_inst in class_set
  Object name is ${obj_inst.Name}
.//  .print "${obj_inst.Name}"
.end for

.emit to file "ex2.txt"
End of List of Object Names

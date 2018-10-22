.//=======================================================================
.//
.// File:      $RCSfile: exercise3.arc,v $
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
.// Exercise 3
.select many class_set from instances of O_OBJ
.for each obj_inst in class_set

    .// class comment followed by class name
    /* class comment */
    class ${obj_inst.Name} {

    .select many attr_set related by obj_inst->O_ATTR[R102]
    .for each attr_inst in attr_set
        .// This is a class attribute (always integer)
        int ${attr_inst.Name}; /* attr comment */
    .end for 

    .// Below is the closing curly for the generated class 
    };
.end for

.emit to file "ex3.txt"


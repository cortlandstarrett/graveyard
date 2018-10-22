.//=======================================================================
.//
.// File:      $RCSfile: exercise5.arc,v $
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
.// Exercise 5
.select many class_set from instances of O_OBJ
.for each class_inst in class_set

    .// class comment followed by class name
    /* class comment */
    class ${class_inst.Name} {

    .// Now iterate over attributes
    .select many attr_set related by class_inst->O_ATTR[R102]
    .for each attr_inst in attr_set

    	.select one attr_type related by attr_inst->S_DT[R114]
        .// This is a class attribute (always integer)
        ${attr_type.Name} ${attr_inst.Name}; /* comment */

    .end for 

    .// Below is the closing curly for the generated class 
    };

    .emit to file "ex5_${class_inst.Name}.class"
.end for


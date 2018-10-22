.//=======================================================================
.//
.// File:      $RCSfile: exercise6.arc,v $
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
.// Exercise 6



.// This function retrieves a C++ type given  model type
.function lookupCPPType
.param integer coreType

    .assign attr_cppType = ""

    .// The MC3020 model defines the 
    .// following as values for "Core Data Types"
    .//
    .if ( coreType == 0 )
 	.// 0 = void
	.assign attr_cppType = "void"
    .elif ( coreType == 1 )
	.// 1 = boolean
	.assign attr_cppType = "char"
    .elif ( coreType == 2 )
	.// 2 = integer
	.assign attr_cppType = "int"
    .elif ( coreType == 3 )
 	.// 3 = real
	.assign attr_cppType = "real"
    .elif ( coreType == 4 )
	.// 4 = string
        .// WARNING! 100 is an arbitrary value
	.assign attr_cppType = "char[100]"
    .elif ( coreType == 5 )
 	.// 5 = integer
	.assign attr_cppType = "int"
    .elif ( coreType == 6 )
 	.// 6 = current_state
	.assign attr_cppType = "void*"
    .elif ( coreType == 7 )
 	.// 7 = same_as_base
	.assign attr_cppType = "void*"
    .elif ( coreType == 8 )
 	.// 8 = inst_ref<Object>
	.assign attr_cppType = "void*"
    .elif ( coreType == 9 )
 	.// 9 = inst_ref_set<Object>
	.assign attr_cppType = "void*"
    .elif ( coreType == 10 )
 	.// 10= inst<Event>
	.assign attr_cppType = "void*"
    .elif ( coreType == 11 )
 	.// 11= inst<Mapping>
	.assign attr_cppType = "void*
    .elif ( coreType == 12 )
 	.// 12= inst_ref<Mapping>
	.assign attr_cppType = "void*"
    .else
	.assign attr_cppType = "Error Unexpected Type (${coreType})"
    .end if
.end function

.// This function retrieves a C++ type given  model type
.function getCPPType
.param inst_ref dt_inst


    .assign attr_modelType = dt_inst.Name
    .assign attr_Core_Type = -1
    .assign attr_cppType = ""
    .assign attr_enumData = ""

    .select one cdt related by dt_inst->S_CDT[R17]
    .select one udt related by dt_inst->S_UDT[R17]
    .select one edt related by dt_inst->S_EDT[R17]

    .if ( not_empty cdt )

	.assign attr_Core_Type = cdt.Core_Typ

	.// Call a function to get the CPP type from this integer value
	.invoke lookupResult = lookupCPPType(attr_Core_Type)
	.assign attr_cppType = lookupResult.cppType

    .elif ( not_empty udt )
	.// Each user data-type maps to a core data type
	select one udt_cdt related by udt->S_CDT[R18]

	assign attr_Core_type = udt_cdt.CoreTyp

	.// Call a function to get the CPP type from this integer value
	.invoke lookupResult = lookupCPPType(attr_Core_Type)
	.assign attr_cppType = lookupResult.cppType

    .elif ( not_empty edt )
	
	.// I'm taking the easy way out and assuming that the
	.// enum definition is made else where and so we can
	.// go ahead and declare this here.
	.// 
	.assign attr_cppType = dt_inst.Name

    .else
	.assign attr_cppType = "Error! (${attr_cppType})"
    .end if

.end function

.select many class_set from instances of O_OBJ
.for each class_inst in class_set

    .// class comment followed by class name
    /* class comment */
    class ${class_inst.Name} {

    .// Now iterate over attributes
    .select many a_set related by class_inst->O_ATTR[R102]
    .for each a_inst in a_set

        .select one dt_inst related by a_inst->S_DT[R114]
	.// Call a function to get the CPP data type
	.invoke myResult = getCPPType(dt_inst)

        .// This is a class attribute (always integer)
        ${myResult.cppType} ${a_inst.Name}; /* comment */

    .end for 

    .// Below is the closing curly for the generated class 
    };

    .emit to file "ex6_${class_inst.Name}.class"
.end for


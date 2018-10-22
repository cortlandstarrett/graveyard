/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _DUMP_CLS_ACTION_HH
#define _DUMP_CLS_ACTION_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2001 by eXcelon Corporation. All Rights Reserved. *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/

//-- Include files -----------------------------------------------------

#include <ostore/traverse/action.hh>
#include <ostore/traverse/cls_act.hh>
#include <ostore/traverse/obj_act.hh>
#include <ostore/traverse/base_act.hh>
#include <ostore/traverse/mem_act.hh>
#include <ostore/traverse/wrp_act.hh>

/** 
* I provide an alternate traversal path required for versions of dumpload
* as of dumpload shipped with 6.0.6. 
*/
class os_Dumper_Class_action : public os_Class_action {
  public:

    os_Dumper_Class_action (os_Base_action* base_action = 0,
      os_Member_variable_action* variable_action = 0,
      os_Member_function_action* function_action = 0,
      os_Member_type_action* type_action = 0,
      os_Member_access_modifier_action* access_modifier_action = 0 );

    ~os_Dumper_Class_action();

    virtual void apply_component_actions  
      (const os_class_type& actual_class, void* object);

    virtual void apply_component_actions 
      (const os_class_type& actual_class);

};

#endif //DUMP_CLS_ACTION_HH

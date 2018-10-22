/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DB_OFFTAB_HH
#define DB_OFFTAB_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
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

#include <ostore/ostore.hh>
#include <ostore/coll.hh>
//#include <ostore/coll/dict_pt.hh>
#include <ostore/traverse/obj_act.hh>
#include <ostore/traverse/pred_act.hh>
#include <ostore/traverse/enum_act.hh>
#include <ostore/traverse/ptr_act.hh>
#include <ostore/traverse/ary_act.hh>
#include <ostore/dumpload/dump_cls_act.hh>
#include <ostore/traverse/base_act.hh>
#include <ostore/traverse/func_act.hh>
#include <ostore/traverse/indr_act.hh>
#include <ostore/traverse/schm_act.hh>
#include <ostore/traverse/traverse.hh>
#include <ostore/traverse/wrp_act.hh>

class os_Offset_displacement_entry
   {
private:
   friend class os_Offset_displacement_table;
   os_Offset_displacement_entry(); // only create from os_Offset_displacement_table
   void insert(char* the_member, os_unsigned_int32 src_offset);
   int build(char* the_member, os_unsigned_int32 dst_offset);
   os_unsigned_int32 offset(os_unsigned_int32 src_offset);
   os_Dictionary<os_unsigned_int32, os_unsigned_int32*> new_offset; // used for offset
   os_Dictionary<char*, os_unsigned_int32*> members; // used to build new_offset
   int used;
   };

class os_Offset_displacement_table
   {
public:
   os_Offset_displacement_table();
   static os_Offset_displacement_table& get(void);
   void insert(char* the_class, char* the_member, os_unsigned_int32 src_offset);
   void build(char* the_class,char* the_member, os_unsigned_int32 dst_offset);
   os_unsigned_int32 offset(char* the_class, os_unsigned_int32 src_offset);
   int is_used(void) {return used;}
private:
   os_Dictionary<char*, os_Offset_displacement_entry*> classes;
   int used;
   };

class os_Offset_displacement_view : protected os_Wrapper_actions
   {
public:
   os_Offset_displacement_view(os_Offset_displacement_table&);
  ~os_Offset_displacement_view();
   void set_insert_pass() { build = 0; }
   void set_build_pass() { build = 1; }
   void view(os_schema&);
   void view(os_class_type&);
protected:
   os_boolean pre_action(const os_class_type& type);
   os_boolean pre_action(const os_base_class& type);
   void post_action(const os_base_class& type);
   os_boolean pre_action(const os_member_variable& member);
   os_Traverser& get_traverser ();
   os_Traverser* traverser;
   char* the_class;
   char* base_name;
   os_Offset_displacement_table& displacement_table;
   int build;
   // These are here so they can be deleted easily.
      os_Predef_action*   predef_action;
      os_Enum_action*     enum_action;
      os_Pointer_action*  pointer_action;
      os_Function_action* function_action;
      os_Array_action*    array_action;
      os_Indirect_action* indirect_action;
      os_Base_action*     base_action;
      os_Member_variable_action* member_variable_action;
      os_Class_action* class_action;
      os_Object_action* object_action;
      os_Schema_action* schema_action;
      os_Database_action* database_action;
   };



#endif /* DB_OFFTAB_HH */

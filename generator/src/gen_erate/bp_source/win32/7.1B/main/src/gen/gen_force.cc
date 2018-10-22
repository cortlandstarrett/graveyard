/*========================================================================
 *
 * File:      $RCSfile: gen_force.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>


class I_Attribute;
class I_Attribute_Instance;

class I_Related_Object_Pair;
class I_Related_Object_Instance_Pair;

class I_SM_Evt_Inst;
class I_SM_Evt_Supp_DI;
class I_SM_Evt_Supp_DI_Inst;

class String;
class Description;
class I_var;

class I_ID_Attribute_Reference ;
class I_Object ;
class I_Object_Instance ;
class I_Relationship ;
class I_SM_Evt ;

void foo_force_vfts(void*) {
      foo_force_vfts(new mc_dbms_Set< class I_Related_Object_Instance_Pair *>);
      foo_force_vfts(new mc_dbms_List< class I_Related_Object_Instance_Pair *>);
      foo_force_vfts(new mc_dbms_Bag< class I_Related_Object_Instance_Pair *>);
      foo_force_vfts(new mc_dbms_Collection< class I_Related_Object_Instance_Pair *>);

      foo_force_vfts(new mc_dbms_Set< class I_Related_Object_Pair *>);
      foo_force_vfts(new mc_dbms_List< class I_Related_Object_Pair *>);
      foo_force_vfts(new mc_dbms_Bag< class I_Related_Object_Pair *>);
      foo_force_vfts(new mc_dbms_Collection< class I_Related_Object_Pair *>);

      foo_force_vfts(new mc_dbms_Set< class String *>);
      foo_force_vfts(new mc_dbms_List< class String *>);
      foo_force_vfts(new mc_dbms_Bag< class String *>);

      foo_force_vfts(new mc_dbms_Set< class I_SM_Evt_Inst *>);
      foo_force_vfts(new mc_dbms_List< class I_SM_Evt_Inst *>);
      foo_force_vfts(new mc_dbms_Bag< class I_SM_Evt_Inst *>);
      foo_force_vfts(new mc_dbms_Collection< class I_SM_Evt_Inst *>);

      foo_force_vfts(new mc_dbms_Set< class I_SM_Evt_Supp_DI_Inst *>);
      foo_force_vfts(new mc_dbms_List< class I_SM_Evt_Supp_DI_Inst *>);
      foo_force_vfts(new mc_dbms_Bag< class I_SM_Evt_Supp_DI_Inst *>);
      foo_force_vfts(new mc_dbms_Collection< class I_SM_Evt_Supp_DI_Inst *>);

      foo_force_vfts(new mc_dbms_Set< class I_SM_Evt_Supp_DI *>);
      foo_force_vfts(new mc_dbms_List< class I_SM_Evt_Supp_DI *>);
      foo_force_vfts(new mc_dbms_Bag< class I_SM_Evt_Supp_DI *>);
      foo_force_vfts(new mc_dbms_Collection< class I_SM_Evt_Supp_DI *>);

      foo_force_vfts(new mc_dbms_Set< class I_var *>);
      foo_force_vfts(new mc_dbms_List< class I_var *>);
      foo_force_vfts(new mc_dbms_Bag< class I_var *>);

      foo_force_vfts(new mc_dbms_Set< class I_Attribute *>);
      foo_force_vfts(new mc_dbms_List< class I_Attribute *>);
      foo_force_vfts(new mc_dbms_Bag< class I_Attribute *>);
      foo_force_vfts(new mc_dbms_Collection< class I_Attribute *>);

      foo_force_vfts(new mc_dbms_Set< class I_Attribute_Instance *>);
      foo_force_vfts(new mc_dbms_List< class I_Attribute_Instance *>);
      foo_force_vfts(new mc_dbms_Bag< class I_Attribute_Instance *>);
      foo_force_vfts(new mc_dbms_Collection< class I_Attribute_Instance *>);

      foo_force_vfts(new mc_dbms_Set< class I_ID_Attribute_Reference *>);
      foo_force_vfts(new mc_dbms_List< class I_ID_Attribute_Reference *>);
      foo_force_vfts(new mc_dbms_Bag< class I_ID_Attribute_Reference *>);
      foo_force_vfts(new mc_dbms_Collection< class I_ID_Attribute_Reference *>);

      foo_force_vfts(new mc_dbms_Set< class I_Object_Instance *>);
      foo_force_vfts(new mc_dbms_List< class I_Object_Instance *>);
      foo_force_vfts(new mc_dbms_Bag< class I_Object_Instance *>);

      foo_force_vfts(new mc_dbms_Collection< class Description *>);
      foo_force_vfts(new mc_dbms_Set< class Description *>);
      foo_force_vfts(new mc_dbms_List< class Description *>);
      foo_force_vfts(new mc_dbms_Bag< class Description *>);

      foo_force_vfts(new mc_dbms_Collection< class I_ID_Attribute_Reference*>);
      foo_force_vfts(new mc_dbms_Collection< class I_Object*>);
      foo_force_vfts(new mc_dbms_Collection< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_Collection< class I_SM_Evt*>);
      foo_force_vfts(new mc_dbms_List< class I_ID_Attribute_Reference*>);
      foo_force_vfts(new mc_dbms_List< class I_Object*>);
      foo_force_vfts(new mc_dbms_List< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_List< class I_SM_Evt*>);
      foo_force_vfts(new mc_dbms_Set< class I_Object*>);
      foo_force_vfts(new mc_dbms_Set< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_Set< class I_SM_Evt*>);

      foo_force_vfts(new mc_dbms_Collection< class I_ID_Attribute_Reference*>);
      foo_force_vfts(new mc_dbms_Collection< class I_Object*>);
      foo_force_vfts(new mc_dbms_Collection< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_Collection< class I_SM_Evt*>);
      foo_force_vfts(new mc_dbms_List< class I_ID_Attribute_Reference*>);
      foo_force_vfts(new mc_dbms_List< class I_Object*>);
      foo_force_vfts(new mc_dbms_List< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_List< class I_SM_Evt*>);
      foo_force_vfts(new mc_dbms_Set< class I_Object*>);
      foo_force_vfts(new mc_dbms_Set< class I_Relationship*>);
      foo_force_vfts(new mc_dbms_Set< class I_SM_Evt*>);
}


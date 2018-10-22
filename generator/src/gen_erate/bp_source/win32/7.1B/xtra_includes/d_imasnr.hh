/*========================================================================
 *
 * File:      $RCSfile: d_imasnr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_IMASNR_HH
#define D_IMASNR_HH

// Include those header files that are DIRECTLY needed by this one.


#include "u_id.hh"

//
// CLASS: D_im_assigners
//
// DESCRIPTION:
//
// REMARKS:
//
//   The order of Id_assigner value_id's is as follows:
//     object_id_assigner_e,
//     imported_object_id_assigner_e,
//     attr_id_assigner_e,
//     ce_id_assigner_e,
//     attr_ref_in_obj_id_assigner_e,
//     relationship_id_assigner_e,
//     obj_in_rel_id_assigner_e,
//     comm_path_id_assigner_e,
//     access_path_id_assigner_e,
//     transformer_id_assigner_e,
//     tfmr_parm_id_assigner_e,
//     ee_in_model_id_assigner_e,
//     //  im_ocm_oam_id_assigner_e,

class GS_string;
class String;
class Description;

class D_im_assigners
{
public:
  enum id_assigner_e
  {
    first_id_assigner_e = 0,
    object_id_assigner_e = first_id_assigner_e,
    imported_object_id_assigner_e,
    attr_id_assigner_e,
    ce_id_assigner_e,
    attr_ref_in_obj_id_assigner_e,
    relationship_id_assigner_e,
    obj_in_rel_id_assigner_e,
    comm_path_id_assigner_e,
    access_path_id_assigner_e,
    transformer_id_assigner_e,
    tfmr_parm_id_assigner_e,
    ee_in_model_id_assigner_e,
    num_id_assigners_e         // This MUST be last in the enums
  };

  static mc_dbms_typespec *get_mc_dbms_typespec();	// implemented by OS
  D_im_assigners(t_uint config_id = 0);
  ~D_im_assigners()
      {}

  Id_assigner &object_id_assigner()              { return v_object_id_assigner; }
  Id_assigner &imported_object_id_assigner()     { return v_imported_object_id_assigner; }
  Id_assigner &attr_id_assigner()                { return v_attr_id_assigner; }
  Id_assigner &ce_id_assigner()                  { return v_ce_id_assigner; }
  Id_assigner &attr_ref_in_object_id_assigner()  { return v_attr_ref_in_obj_id_assigner; }
  Id_assigner &relationship_id_assigner()        { return v_relationship_id_assigner; }
  Id_assigner &obj_in_rel_id_assigner()          { return v_obj_in_rel_id_assigner; }
  Id_assigner &comm_path_id_assigner()           { return v_comm_path_id_assigner; }
  Id_assigner &access_path_id_assigner()         { return v_access_path_id_assigner; }
  Id_assigner &transformer_id_assigner()         { return v_transformer_id_assigner; }
  Id_assigner &tfmr_parm_id_assigner()           { return v_tfmr_parm_id_assigner; }
  Id_assigner &ext_entity_in_model_id_assigner() { return v_ee_in_model_id_assigner; }

  t_boolean update_id_assigners( GS_string & config_data_info,
                                 String & p_err_msg );
  t_boolean update_config_data_info( const Description & p_config_data_info,
                                     String & p_err_msg );
  int num_assigners() { return (int)num_id_assigners_e; }

  void reset_index( t_uint &index ) { index = first_id_assigner_e; }
  t_boolean assign_next_value( t_uint &index, t_uint value );
  t_uint get_next_value( t_uint &index );
  t_uint get_index( t_uint &index ) { return index; }

private:

  Id_assigner v_object_id_assigner;
  Id_assigner v_imported_object_id_assigner;
  Id_assigner v_attr_id_assigner;
  Id_assigner v_ce_id_assigner;
  Id_assigner v_attr_ref_in_obj_id_assigner;
  Id_assigner v_relationship_id_assigner;
  Id_assigner v_obj_in_rel_id_assigner;
  Id_assigner v_comm_path_id_assigner;
  Id_assigner v_access_path_id_assigner;
  Id_assigner v_transformer_id_assigner;
  Id_assigner v_tfmr_parm_id_assigner;
  Id_assigner v_ee_in_model_id_assigner;

};

#endif /* D_IMASNR_HH */

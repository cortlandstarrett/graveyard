/*========================================================================
 *
 * File:      $RCSfile: d_smasnr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_SMASNR_HH
#define D_SMASNR_HH

// Include those header files that are DIRECTLY needed by this one.


#include "u_id.hh"

//
// CLASS: D_sm_assigners
//
// DESCRIPTION:
//
// REMARKS:
//
//   The order of Id_assigner value_id's is as follows:
//     action_id_assigner_e,
//     drv_comm_path_id_assigner_e,
//     drv_access_path_id_assigner_e,
//     sm_edi_id_assigner_e,
//     sm_event_id_assigner_e,
//     sm_state_id_assigner_e,
//     supp_data_id_assigner_e,
//     transition_id_assigner_e,
//     ce_id_assigner_e

class GS_string;
class String;
class Description;

class D_sm_assigners
{
public:
  enum id_assigner_e
  {
    first_id_assigner_e = 0,
    action_id_assigner_e = first_id_assigner_e,
    drv_comm_path_id_assigner_e,
    drv_access_path_id_assigner_e,
    sm_edi_id_assigner_e,
    sm_event_id_assigner_e,
    sm_state_id_assigner_e,
    supp_data_id_assigner_e,
    transition_id_assigner_e,
    ce_id_assigner_e,
    num_id_assigners_e         // This MUST be last in the enums
  };

  static mc_dbms_typespec *get_mc_dbms_typespec();	// implemented by OS
  D_sm_assigners(t_uint config_id = 0);
  ~D_sm_assigners()
      {}

  Id_assigner &action_id_assigner()          { return v_action_id_assigner; }
  Id_assigner &drv_comm_path_id_assigner()   { return v_drv_comm_path_id_assigner; }
  Id_assigner &drv_access_path_id_assigner() { return v_drv_access_path_id_assigner; }
  Id_assigner &sm_edi_id_assigner()          { return v_sm_edi_id_assigner; }
  Id_assigner &sm_event_id_assigner()        { return v_sm_event_id_assigner; }
  Id_assigner &sm_state_id_assigner()        { return v_sm_state_id_assigner; }
  Id_assigner &supp_data_id_assigner()       { return v_supp_data_id_assigner; }
  Id_assigner &transition_id_assigner()      { return v_transition_id_assigner; }
  Id_assigner &ce_id_assigner()              { return v_ce_id_assigner; }

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
  
  Id_assigner v_action_id_assigner;
  Id_assigner v_drv_comm_path_id_assigner;
  Id_assigner v_drv_access_path_id_assigner;
  Id_assigner v_sm_edi_id_assigner;
  Id_assigner v_sm_event_id_assigner;
  Id_assigner v_sm_state_id_assigner;
  Id_assigner v_supp_data_id_assigner;
  Id_assigner v_transition_id_assigner;
  Id_assigner v_ce_id_assigner;

};

#endif /* D_SMASNR_HH */

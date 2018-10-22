/*========================================================================
 *
 * File:      $RCSfile: d_ddasnr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:06 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_DDASNR_HH
#define D_DDASNR_HH

// Include those header files that are DIRECTLY needed by this one.


#include "u_id.hh"

//
// CLASS: D_dd_assigners
//
// DESCRIPTION:
//
// REMARKS:
//
//   The order of Id_assigner value_id's is as follows:
//       _data_type_id_assigner,
//       _enumerator_id_assigner,
//       _synch_service_id_assigner,
//       _bridge_id_assigner,
//       _parameter_id_assigner,
//       _ext_entity_id_assigner,
//       _ext_entity_event_id_assigner,
//       _ext_entity_edi_id_assigner,
//       _ext_entity_di_id_assigner,
//       _ce_id_assigner,
//

class GS_string;
class String;
class Description;

class D_dd_assigners
{
public:
  enum id_assigner_e
  {
    first_id_assigner_e = 0,
    data_type_id_assigner_e = first_id_assigner_e,
    enumerator_id_assigner_e,
    synch_svc_id_assigner_e,
    bridge_id_assigner_e,
    parameter_id_assigner_e,
    subsystem_id_assigner_e,
    ee_id_assigner_e,
    ee_event_id_assigner_e,
    ee_edi_id_assigner_e,
    ee_di_id_assigner_e,
    ce_id_assigner_e,
    num_id_assigners_e         // This MUST be last in the enums
  };

  static mc_dbms_typespec *get_mc_dbms_typespec();	// implemented by OS
  D_dd_assigners(t_uint config_id = 0);
  ~D_dd_assigners()
      {}

  Id_assigner &data_type_id_assigner()  { return v_data_type_id_assigner; }
  Id_assigner &enumerator_id_assigner() { return v_enumerator_id_assigner; }
  Id_assigner &synch_service_id_assigner()  { return v_synch_svc_id_assigner;}
  Id_assigner &bridge_id_assigner()     { return v_bridge_id_assigner; }
  Id_assigner &parameter_id_assigner()  { return v_parameter_id_assigner; }
  Id_assigner &subsystem_id_assigner()         { return v_subsystem_id_assigner; }
  Id_assigner &ext_entity_id_assigner()         { return v_ee_id_assigner; }
  Id_assigner &ext_entity_event_id_assigner()   { return v_ee_event_id_assigner; }
  Id_assigner &ext_entity_edi_id_assigner()     { return v_ee_edi_id_assigner; }
  Id_assigner &ext_entity_di_id_assigner()      { return v_ee_di_id_assigner; }
  Id_assigner &ce_id_assigner()         { return v_ce_id_assigner; }

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

  Id_assigner v_data_type_id_assigner;
  Id_assigner v_enumerator_id_assigner;
  Id_assigner v_synch_svc_id_assigner;
  Id_assigner v_bridge_id_assigner;
  Id_assigner v_parameter_id_assigner;
  Id_assigner v_subsystem_id_assigner;
  Id_assigner v_ee_id_assigner;
  Id_assigner v_ee_event_id_assigner;
  Id_assigner v_ee_edi_id_assigner;
  Id_assigner v_ee_di_id_assigner;
  Id_assigner v_ce_id_assigner;

};

#endif /* D_DDASNR_HH */

/*========================================================================
 *
 * File:      $RCSfile: d_sm_pm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:07 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_SM_PM_HH
#define D_SM_PM_HH

//
// FILE: D_sm_pm.hh
//
// CONTENTS: Specification of a versioned Domain object. This in essence is
//	a DD_SM_SPT_PM object that can be versioned, each version of which
//	corresponds to a single version of a state machine.
//
// REMARKS: 
//


// Include those header files that are DIRECTLY needed by this one.


#include <u_typdef.hh>
#include <u_id.hh>
#include <u_string.hh>
#include <u_desc.hh>

#include <d_typdef.hh>
#include <d_domid.hh>
#include <d_domain.hh>
#include <d_vertag.hh>
#include <d_sm_ver.hh>
#include <d_object.hh>
#include <d_smasnr.hh>

#include <u_cursor.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.

class D_sm_state;
class D_sm_event;
class D_sm_event_data_item;
class D_local_event;
class D_polymorphic_event;
class D_non_local_event;
class D_supplemental_data;
class D_transition;
class D_no_event_transition;
class D_creation_transition;
class D_sm;
class D_action;
class D_derived_communication_path;
class D_derived_access_path;
class M_sm;


//
// CLASS: D_sm_spt_pm
//
// DESCRIPTION:
//
// REMARKS:
//

class D_sm_spt_pm
{
public:
  enum t_sm_spt_pm_type { ASSIGNER_SM, INSTANCE_SM };
  
  //  MANAGER functions
  
  static mc_dbms_typespec* get_mc_dbms_typespec ();
  mc_dbms_segment *get_config_ptr() { return mc_dbms_segment::of( this ); }
  mc_dbms_database *get_db_ptr() const { return get_domain_ptr()->get_db_ptr(); }
  
  //  IMPLEMENTOR functions

  int find_all_dangling_relationships ( t_boolean p_do_dt_tests,
                      mc_dbms_List<Description*> &p_dangle_list,
                      const Description& p_domain_name, 
                      const Description& p_subsys_name,
                      e_diagram_display_mode dm );
  
  // Version Management functions.
  
	// !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	// The following version management functions require that the
	// caller had better NOT be in a transaction.
  
  static t_boolean checkout_sm_spt_pm( const Domain_id &p_domain_id,
                                       const Id &p_sm_spt_pm_id,
                                       const t_boolean p_end_branch,
                                       const t_boolean p_reserved,
                                       const Description &p_target_branch_name,
                                       String &p_err_msg );
  
  static t_boolean uncheckout_sm_spt_pm( const Domain_id &p_domain_id,
                                         const Id &p_sm_spt_pm_id,
                                         String &p_err_msg );
  
  static t_boolean browse_sm_spt_pm( const Domain_id &p_domain_id,
                                     const Id &p_sm_spt_pm_id,
                                     String &p_err_msg,
                                     const Description &p_branch_name,
                                     const float p_origin_version_num );
  
  static t_boolean checkin_sm_spt_pm( const Domain_id &p_domain_id,
                                      const Id &p_sm_spt_pm_id,
                                      const Description &p_target_branch_name, 
                                      const float p_new_version_num,
                                      const t_boolean p_pinned,
                                      String &p_err_msg);
  
	// The following is for storing away config/version info in a
	// control file that we use when we checkin. It MUST be called prior
	// to checkin! It returns the new version number (-1.0 if error).
  // Note that it can be called an indefinite number of times prior
  // to checkin, so we only want to output the control info file
  // without updating any persistent data.
  
	static void pre_checkin( const Domain_id &p_domain_id,
                           const Id &p_sm_spt_pm_id,
                           Description &p_config_data_info );
  

	// !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// The following version management functions require that the
	// caller had BETTER be in a transaction.
  
  static t_boolean is_ok_to_delete( const Domain_id &p_domain_id,
                                    const Id &p_sm_spt_pm_id,
                                    String &p_err_msg,
                                    const Description &p_branch_name,
                                    float p_version_num );
  
  static t_boolean is_checked_out( const Domain_id &p_domain_id,
                                   const Id &p_sm_spt_pm_id,
                                   D_version_tag &p_version_tag );

  static t_boolean is_checked_out_by_me( const Domain_id &p_domain_id,
                                         const Id &p_sm_spt_pm_id );

  t_boolean is_checked_out();
  
  t_boolean is_checked_out_by_me();

  t_boolean is_first_version();
  t_boolean is_last_version();
  t_boolean is_branch_version();

  D_sm_version_info *get_ver_ptr() const
    { return m_sm_ver_ptr; }

  void clear_all_exported_flags();

  // CREATION functions
  
	// Create a new state model (configuration).  It will be version 1.0
	// and marked as checked in.
  static Id create_new_state_model ( Domain *p_domain_ptr,
                                     t_sm_spt_pm_type p_sm_spt_pm_type,
                                     const Description &p_branch_name,
                                     float p_version_num );
  static Id create_new_state_model ( Domain *p_domain_ptr,
                                     const Id & p_id,
                                     t_sm_spt_pm_type p_sm_spt_pm_type,
                                     const Description &p_branch_name,
                                     float p_version_num );
  
	// Create a version of an existing state model (configuration).
  static D_sm_spt_pm *create_state_model ( Domain *p_domain_ptr,
                                           const Id & p_id,
                                           t_sm_spt_pm_type p_sm_spt_pm_type,
                                           const Description &p_branch_name,
                                           float p_version_num );

  // DELETION functions

  // Delete the current version
  t_boolean destroy_sm_version( String &p_err_msg);
  void delete_sm_spt_pm ();
  ~D_sm_spt_pm ();
    
  // MISCELLANEOUS access functions

  D_version_tag &version_tag()
      { return ver_tag; }

  t_boolean is_viewed_version() const
      { return (this == get_ver_ptr()->get_cur_sm_ptr())? TRUE: FALSE; }

  D_sm_assigners *get_assigners()
    { return assigners; }

  // Related MODEL functions
  
  M_sm* get_M_sm_ptr () { return m_M_sm_ptr; }
  
  // ITERATOR and FIND/QUERY functions.

  D_cp_sm_spt_pm* copy_sm_spt_pm ();
  // paste_sm_spt_pm is implemented by D_cp_sm_spt_pm

  t_uint get_number_of_sm_states ()
    { return (t_uint) get_sm_state_coll_ptr ()->cardinality (); }
  
  D_sm_state* find_sm_state_by_id (const Id & p_id);
  
  t_uint get_number_of_sm_events ()
    { return (t_uint) get_sm_event_coll_ptr ()->cardinality (); }
  
  D_sm_event* find_sm_event_by_id (const Id & p_id);
  
  D_sm_event_data_item* find_sm_event_data_item_by_id (const Id & p_id);
  
  t_uint get_number_of_transitions ()
    { return (t_uint) get_transition_coll_ptr ()->cardinality (); }
  
  D_transition* find_transition_by_id (Id);
  
  t_uint get_number_of_actions ()
    { return (t_uint) get_action_coll_ptr ()->cardinality (); }
  
  D_action* find_action_by_id (Id);
  
	D_derived_communication_path* find_comm_path_by_dest_id (const Id & p_id);
	D_derived_access_path* find_access_path_by_dest_id (const Id & p_id);
  
  
  D_sm_state* create_sm_state ();
  D_sm_state* create_sm_state (const Id & p_id);
  
  D_polymorphic_event* create_poly_event (t_boolean p_create_supp_data = TRUE);
  D_polymorphic_event* create_poly_event (const Id & p_id,
                               t_boolean p_create_supp_data = TRUE);
  D_local_event* create_local_event (t_boolean p_create_supp_data = TRUE);
  D_local_event* create_local_event (const Id & p_id,
                               t_boolean p_create_supp_data = TRUE);
  D_non_local_event* create_non_local_event (t_boolean p_create_supp_data);
  D_non_local_event* create_non_local_event (const Id & p_id,
                               t_boolean p_create_supp_data);
  
	D_sm_event_data_item* create_sm_event_data_item ();
	D_sm_event_data_item* create_sm_event_data_item (const Id & p_id);
  
  D_transition* create_transition ();
  
	D_no_event_transition* create_no_event_transition ();
	D_no_event_transition* create_no_event_transition (const Id & p_id);
  
	D_creation_transition* create_creation_transition ();
	D_creation_transition* create_creation_transition (const Id & p_id);
  
  D_sm* create_sm ();
  
  D_action* create_action ();
  
	D_derived_access_path* create_derived_access_path (const Id &dest_id);
  
	D_derived_communication_path*
    create_derived_communication_path (const Id &dest_id);
  
  
	t_boolean audit_state_event_matrix (Description &p_err_msg);
  
	t_boolean combine_supplemental_data (Description &p_err_msg, t_boolean p_delete_old_refs);
  
	static void synchronize_non_local_events
	   (D_sm_spt_pm* p_super_sm_ptr, D_sm_spt_pm* p_sub_sm_ptr, t_boolean p_readonly, 
        Description& p_err_msg, t_boolean p_delete_old_refs);

  t_boolean verify_poly_event_unused( D_polymorphic_event* );

  //  ACCESS functions.

  const Id & get_id() const { return m_id; }
  t_uint get_config_id() const { return get_id().get_config_id(); }
  Domain *get_domain_ptr() const { return get_ver_ptr()->get_domain_ptr(); }
  Domain_id get_domain_id() const { return get_domain_ptr()->get_domain_id(); }

	Description &description () { return _description; }
  
  Object *get_object_ptr();
  
  D_im_ocm_oam *get_im_ocm_oam_ptr();
  
  D_subsys *get_dd_subsystem_ptr() const;
  
  D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr();
  
  t_sm_spt_pm_type get_sm_spt_pm_type()
	  { return sm_spt_pm_type; }
  void set_sm_spt_pm_type( t_sm_spt_pm_type p_sm_spt_pm_type )
	  { sm_spt_pm_type = p_sm_spt_pm_type; }
  
  mc_dbms_List<D_sm_state*> *get_sm_state_coll_ptr ()
    { return &(m_sm_state_coll.getvalue ()); }
  
  mc_dbms_List<D_sm_event*> *get_sm_event_coll_ptr ()
    { return &(m_sm_event_coll.getvalue ()); }
  
  mc_dbms_List<D_sm_event_data_item*> *get_sm_event_data_item_coll_ptr ()
    { return &(m_sm_event_data_item_coll.getvalue ()); }

  mc_dbms_List<D_supplemental_data*> *get_supplemental_data_coll_ptr ()
    { return &(m_supplemental_data_coll.getvalue ()); }

  mc_dbms_List<D_transition*> *get_transition_coll_ptr ()
    { return &(m_transition_coll.getvalue ()); }

  mc_dbms_List<D_derived_communication_path*> *get_derived_comm_path_coll_ptr ()
    { return &(m_derived_communication_path_coll.getvalue ()); }

  mc_dbms_List<D_derived_access_path*> *get_derived_access_path_coll_ptr ()
    { return &(m_derived_access_path_coll.getvalue ()); }

  D_sm* get_sm_ptr () { return m_sm_ptr; }
  void set_sm_ptr (D_sm* p_sm_ptr) { m_sm_ptr = p_sm_ptr; }

  mc_dbms_List<D_action*> *get_action_coll_ptr ()
	  { return &(m_action_coll.getvalue ()); }
  
  DELETE_DOWN_DECL_SUBTYPE()

private:
  
  Id m_id;	// same for all versions of this state machine
	Description _description;
  t_boolean viewed_version;
  D_version_tag ver_tag;
  D_sm_assigners *assigners;

  // If TRUE, nothing here but this instance; no underlying data
  t_boolean sm_placeholder;

	t_sm_spt_pm_type sm_spt_pm_type;
  
  // HELPING FUNCTIONS
  
  D_sm_spt_pm (D_sm_version_info *p_ver_ptr,
               const Id & p_id,
               t_sm_spt_pm_type p_sm_spt_pm_type,
               const Description &p_target_branch_name,
               float p_version_num,
               t_boolean p_sm_placeholder);
  
  t_boolean is_sm_placeholder() { return sm_placeholder; }
  
  t_boolean update_id_assigners( GS_string & p_id_assigner_info,
                                 String & p_err_msg );

  mc_dbms_relationship_1_m(D_sm_spt_pm,m_sm_ver_ptr,D_sm_version_info,m_sm_spt_pm_ver_coll,D_sm_version_info *) m_sm_ver_ptr;
  mc_dbms_relationship_1_1(D_sm_spt_pm,m_M_sm_ptr,M_sm,m_D_sm_spt_pm_ptr,M_sm*) m_M_sm_ptr;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_sm_state_coll,D_sm_state,m_sm_spt_pm_ptr,mc_dbms_List<D_sm_state*>) m_sm_state_coll;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_sm_event_coll,D_sm_event,m_sm_spt_pm_ptr,mc_dbms_List<D_sm_event*>) m_sm_event_coll;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_sm_event_data_item_coll,D_sm_event_data_item,m_sm_spt_pm_ptr,mc_dbms_List<D_sm_event_data_item*>) m_sm_event_data_item_coll;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_supplemental_data_coll,D_supplemental_data,m_sm_spt_pm_ptr,mc_dbms_List<D_supplemental_data*>) m_supplemental_data_coll;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_transition_coll,D_transition,m_sm_spt_pm_ptr,mc_dbms_List<D_transition*>) m_transition_coll;
  mc_dbms_relationship_1_1(D_sm_spt_pm,m_sm_ptr,D_sm,m_sm_spt_pm_ptr,D_sm*) m_sm_ptr;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_action_coll,D_action,m_sm_spt_pm_ptr,mc_dbms_List<D_action*>) m_action_coll;
  
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_derived_communication_path_coll,D_derived_communication_path,m_sm_spt_pm_ptr,mc_dbms_List<D_derived_communication_path*>) m_derived_communication_path_coll;
  mc_dbms_relationship_m_1(D_sm_spt_pm,m_derived_access_path_coll,D_derived_access_path,m_sm_spt_pm_ptr,mc_dbms_List<D_derived_access_path*>) m_derived_access_path_coll;

};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//

/*========================================================================
 *
 * File:      $RCSfile: d_dd_sam.hh,v $
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

#ifndef D_DD_SAM_HH
#define D_DD_SAM_HH

//
// FILE: D_dd_sam.hh  AUTHOR: David E. Solomon	CREATION DATE: 3/1/93
//
// CONTENTS: Specification of a versioned Domain object. This in essence is
//	a DD_SRM_SCM_SAM object that can be versioned, each version of which
//	consists of (possibly) different Subsystems.
//
// REMARKS: 
//


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_string.hh>
#include <u_desc.hh>

#include "d_typdef.hh"
#include "d_domid.hh"
#include "d_domain.hh"
#include "d_dd_ver.hh"
#include "d_vertag.hh"
#include "d_ddasnr.hh"

#include <u_string.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros




//  Declare all classes referenced in this file to reduce the
//    need to include the header files.

class M_dd;
class M_srm;
class M_scm;
class M_sam;
class D_subsys;
class D_external_entity;
class D_external_entity_in_model;
class D_data_type;
class D_core_data_type;
class D_user_data_type;
class D_enum_data_type;
class D_synchronous_service;
class D_polymorphic_event;
class D_enumerator;
class Relationship;

//
// CLASS: D_dd_srm_scm_sam
//
// DESCRIPTION:
//
// REMARKS:
//

class D_dd_srm_scm_sam
{
public:
  // MANAGER functions
  
  static mc_dbms_typespec *get_mc_dbms_typespec();	// implemented by OS
  mc_dbms_segment *get_config_ptr() { return mc_dbms_segment::of( this ); }
  mc_dbms_database *get_db_ptr() const { return get_domain_ptr()->get_db_ptr(); }
  
  // IMPLEMENTOR functions
  
  // Version Management functions.

  // !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // The following version management functions require that the
  // caller had better NOT be in a transaction.

  static t_boolean checkout_dd_srm_scm_sam(const Domain_id &p_domain_id,
                                           const t_boolean p_end_branch,
                                           const t_boolean p_reserved,
                                           const Description &p_target_branch_name,
                                           String &p_err_msg);

  static t_boolean uncheckout_dd_srm_scm_sam(const Domain_id &p_domain_id,
                                             String &p_err_msg);
  
  static t_boolean browse_dd_srm_scm_sam( const Domain_id &p_domain_id,
                                          String &p_err_msg,
                                          const Description &p_branch_name,
                                          const float p_origin_version_num );
  
  static t_boolean checkin_dd_srm_scm_sam( const Domain_id &p_domain_id,
                                           const Description &p_target_branch_name,
                                           const float p_new_version_num,
                                           const t_boolean p_pinned,
                                           String &p_err_msg );
  
  // The following is for storing away config/version info in a
  // control file that we use when we checkin. It MUST be called prior
  // to checkin! It returns the new version number (-1.0 if error).
  // Note that it can be called an indefinite number of times prior
  // to checkin, so we only want to output the control info file
  // without updating any persistent data.
  
  static void pre_checkin( const Domain_id &p_domain_id,
                           Description &p_config_data_info );

  // !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // The following version management functions require that the
  // caller had BETTER be in a transaction.

  static t_boolean is_ok_to_delete( const Domain_id &p_domain_id,
                                    String &p_err_msg,
                                    const Description &p_branch_name,
                                    float p_version_num );

  static t_boolean is_checked_out( const Domain_id &p_domain_id,
                                   D_version_tag &p_version_tag );

  static t_boolean is_checked_out_by_me( const Domain_id &p_domain_id );

  t_boolean is_checked_out();
  
  t_boolean is_checked_out_by_me();

  t_boolean is_first_version();
  t_boolean is_last_version();
  t_boolean is_branch_version();
  
  D_dd_version_info *get_ver_ptr() const
    { return m_dd_ver_ptr; }

  // CREATION functions

  static D_dd_srm_scm_sam *create_dd_srm_scm_sam( const Domain_id &p_domain_id,
                                                  const Description &p_branch_name,
                                                  t_ulong p_version_num );
  static D_dd_srm_scm_sam *create_dd_srm_scm_sam( const Domain_id &p_domain_id,
                                                  t_uint config_id,
                                                  const Description &p_branch_name,
                                                  t_ulong p_version_num );
  
  // When a Domain is created, we automatically create a D_dd_srm_scm_sam
  // instance. When the changes corresponding to this first version are
  // complete, they can call checkin_dd_srm_scm_sam. Thereafter, the
  // user needs to call checkout_dd_srm_scm_sam()
  // and a new version will be created; if a previous version is still
  // checked out, then the returned pointer will be 0 and an appropriate
  // error message will be formatted.

  D_subsys *create_subsystem( const Description &p_name,
                              t_uint p_config_id,
                              const Description &p_target_branch_name,
                              float p_version_num );
  D_subsys *create_subsystem( const Description &p_name,
                              const Id & p_id,
                              t_uint p_config_id,
                              const Description &p_target_branch_name,
                              float p_version_num );
  D_subsys *create_subsystem( const Description &p_name,
                              const Id & p_im_id );

  // DELETION functions

  // Delete the current version
  t_boolean destroy_dd_version(String &p_err_msg);
  void delete_dd_srm_sam_scm();
  ~D_dd_srm_scm_sam();
  void delete_subsystem( const Id &p_id );
  
  // MISCELLANEOUS access functions
  
  D_version_tag &version_tag()
      { return ver_tag; }

  t_boolean is_viewed_version() const
      { return (this == get_ver_ptr()->get_cur_dd_ptr())? TRUE: FALSE; }

  D_dd_assigners *get_assigners()
    { return assigners; }

  // Related MODEL functions
  
  M_dd *get_M_dd_ptr() const { return dd_ptr; }
  M_srm *get_M_srm_ptr() const { return srm_ptr; }
  M_scm *get_M_scm_ptr() const { return scm_ptr; }
  M_sam *get_M_sam_ptr() const { return sam_ptr; }
  
  // ITERATOR and FIND/QUERY functions.
  
  long repair_referential_attributes ();
  
  D_subsys *find_subsystem_by_id( const Id &p_id );
  D_subsys *find_subsystem_by_im_ocm_oam_id( const Id &p_id );
  D_subsys *find_subsystem_by_name( const vchar *p_name );

  mc_dbms_List<D_subsys *> *get_dd_subsystem_coll_ptr()
    { return &subsystem_dd_coll.getvalue(); }
  
  D_external_entity *find_external_entity_by_id( const Id &p_id );
  D_external_entity *find_external_entity_by_kl( const Description &p_keylett );

  mc_dbms_List< D_external_entity_in_model * > *get_external_entity_in_model_coll_ptr( const Id &cut_id );

  D_im_ocm_oam *find_im_ocm_oam_by_id( const Id &p_id );

  D_synchronous_service *find_synch_service_by_id( const Id &p_id );
  D_synchronous_service *find_synch_service_by_name( const Description &p_name );

  D_polymorphic_event *find_polymorphic_event_by_id2(       // i2822.1.2 modified
                const Id &p_sm_evt_id, const Id &p_sm_id ); // i2822.1.2 modified

  Relationship * find_relationship_by_id( const Id &p_id );
  void clear_all_exported_flags();

  // ACCESS functions.
  
  const Id & get_id() const { return id; }
  t_uint get_config_id() const { return get_id().get_config_id(); }
  Domain *get_domain_ptr() const { return get_ver_ptr()->get_domain_ptr(); }
  Domain_id get_domain_id() const { return get_domain_ptr()->get_domain_id(); }
  
  Description &domain_description() { return domain_desc; }

  void	make_fully_derived ();
  void	make_partially_derived ();
  t_boolean is_fully_derived () { return fully_derived_flag; }

  D_core_data_type * create_core_data_type
    (const String &p_name);
  D_user_data_type * create_user_data_type (const Description &p_name, const Id &p_core_id);
  D_user_data_type * create_user_data_type (const vchar *p_name, const Id &p_core_id);
  D_user_data_type * create_user_data_type (const Description &p_name, const Id &p_core_id, const Id & p_id);

  D_enum_data_type * create_enum_data_type (const Description &p_name);
  D_enum_data_type * create_enum_data_type (const Description &p_name, const Id & p_id);
  
  D_data_type * find_data_type_by_id    (const Id &p_id);
  D_data_type * find_data_type_by_name (const Description &p_name);
  D_user_data_type * find_user_data_type_by_name (const Description &p_name);
  D_enum_data_type * find_enum_data_type_by_name (const Description &p_name);
  D_core_data_type * find_data_type_by_type (t_core_data_type);
  D_user_data_type * find_user_data_type_by_service_map (t_user_data_type);
  D_enumerator * find_enumerator_by_id    (const Id &p_id);

  mc_dbms_List< D_data_type * > *get_data_type_coll_ptr ()
    { return &(m_data_type_coll.getvalue ()); }
  mc_dbms_List< D_external_entity * > *get_external_entity_coll_ptr()
    { return &external_entity_coll.getvalue(); }
  mc_dbms_List< D_synchronous_service * > *get_synch_service_coll_ptr()
    { return &synch_service_coll.getvalue(); }

  DELETE_DOWN_DECL_SUBTYPE()




private:
  Domain *domain_ptr;
  Id id;
  t_boolean fully_derived_flag;
  Description domain_desc;
  D_version_tag ver_tag;
  D_dd_assigners *assigners;

  // These graphical model handles associate this D_subsys with the
  // corresponding graphical elements. These are maintained strictly
  // by the User.

  // HELPING functions.

  // Normally these would be invoked by User, but instead they will
  // only be invoked locally within the static create function.

  D_dd_srm_scm_sam( Domain *p_domain_ptr,
                    D_dd_version_info *p_dd_ver_ptr,
                    t_uint config_id,
                    const Description &p_branch_name,
                    t_ulong p_version_num );

  t_boolean update_id_assigners( GS_string & p_id_assigner_info,
                                 String & p_err_msg );

  mc_dbms_relationship_1_m(D_dd_srm_scm_sam,m_dd_ver_ptr,D_dd_version_info,m_dd_srm_scm_sam_ver_coll,D_dd_version_info*) m_dd_ver_ptr;

  mc_dbms_relationship_1_1(D_dd_srm_scm_sam,dd_ptr,M_dd,dd_srm_scm_sam_ptr,M_dd *) dd_ptr;
  mc_dbms_relationship_1_1(D_dd_srm_scm_sam,srm_ptr,M_srm,dd_srm_scm_sam_ptr,M_srm *) srm_ptr;
  mc_dbms_relationship_1_1(D_dd_srm_scm_sam,scm_ptr,M_scm,dd_srm_scm_sam_ptr,M_scm *) scm_ptr;
  mc_dbms_relationship_1_1(D_dd_srm_scm_sam,sam_ptr,M_sam,dd_srm_scm_sam_ptr,M_sam *) sam_ptr;
  mc_dbms_relationship_m_1(D_dd_srm_scm_sam,m_data_type_coll,D_data_type,m_dd_srm_scm_sam_ptr,mc_dbms_List< D_data_type * >) m_data_type_coll;
 
  mc_dbms_relationship_m_1(D_dd_srm_scm_sam,external_entity_coll,D_external_entity,dd_srm_scm_sam_ptr,mc_dbms_List< D_external_entity * >) external_entity_coll;

  mc_dbms_relationship_m_1(D_dd_srm_scm_sam,synch_service_coll,D_synchronous_service,m_dd_srm_scm_sam_ptr,mc_dbms_List< D_synchronous_service * >) synch_service_coll;

  mc_dbms_relationship_m_1(D_dd_srm_scm_sam,subsystem_dd_coll,D_subsys,dd_srm_scm_sam_ptr,mc_dbms_List<D_subsys *>) subsystem_dd_coll;

};

#endif /* D_DD_SRM_SCM_SAM_HH */

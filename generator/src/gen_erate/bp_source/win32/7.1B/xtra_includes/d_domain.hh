/*========================================================================
 *
 * File:      $RCSfile: d_domain.hh,v $
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

#ifndef D_DOMAIN_HH
#define D_DOMAIN_HH




//
// FILE: D_domain.hh	AUTHOR: David E. Solomon	CREATION DATE: 11/6/92
//
// CONTENTS:
//
//		This file describes the C++ classes relating to an OOA Domain.
//
// REMARKS:
//
//		A domain is the most abstract object and highest-level object in
//		the Shlaer/Mellor OOA Universe.
//
//		Instances of these objects will be persistent.
//
//		The OOAmaker invocation will be with one or more domains;
//		accordingly, each Invocation(instance) will contain a collection
//		of these Domain instances.
//
//		Once we open the MC_DBMS database associated with a given domain,
//		we navigate to its corresponding persistent OOA data via a pointer
//		to its one and only Domain instance, which serves as the database
//		root. We will save a pointer to this instance in an MC_DBMS reference so
//		we don't have to continuously find the root which is expensive.
//


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_desc.hh>
#include <u_string.hh>

#include "d_typdef.hh"
#include "d_domid.hh"
#include "d_dd_ver.hh"
#include "d_im_ver.hh"
#include "d_sm_ver.hh"
#include "d_vertag.hh"


// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Domain;

// Also declare classes in other subsystem that we reference, but don't
// include header file.

class Basic_object;
class Object;
class Object_in_relationship;
class Object_as_supertype;
class Object_as_subtype;
class Object_identifier_attribute;
class Object_referred_to;
class Object_referring;
class Imported_object;
class D_dd_srm_scm_sam;
class D_subsys;
class D_im_ocm_oam;
class D_sm_spt_pm;
class Referred_to_ident_attr;
class Attr_ref_in_object;
class Relationship;
class D_access_path;
class D_communication_path;
class D_entity;
class D_external_entity_in_model;

//
// CLASS: Domain
//
// DESCRIPTION:
//
//		This defines the basic OOA Domain.
//
// REMARKS:
//
//		A Domain is the highest level object in the Shlaer/Mellor OOA
//		Universe.
//
//		A Domain will consist of a collection of Subsystems. For efficiency
//		and ease-of-use, we will store this pointer to the collection of
//		Subsystems in an MC_DBMS reference.
//
//		The concept of Model is not relevant to our OOA Data Domain(generic)
//		but instead to the Presentation Domain(generic).
//
//		IMPORTANT: This is a presistent class that is created upon
//		invocation of OOAmaker. The constructor arguments are the
//		database file name and the directory name of the UNIX file that
//		serves as the MC_DBMS database of this domain(the ending file
//		name of the full path name will be same as domain name).
//
//		Also note that we will maintain a set of all Objects within a given
//		Domain. This is in essence a class-extent since we only have one
//		Domain per database. However, this class-extent contains objects
//		across all Subsystems. A User may also access those Objects within
//		a given Subsystem with the Subsystem member functions on Objects.
//

class Domain
{
public:
  static const char *const DOMAIN_ROOT;
  
  // MANAGER functions
  
  static mc_dbms_typespec *get_mc_dbms_typespec();	// implemented by OS
  
  // IMPLEMENTOR functions
  
  // When we create/open databases, we will add them to our collection
  // of MC_DBMS references to domain instances, each of which resides in
  // a different database. The "create_database" function will create
  // the new Domain instance.
  //
  // The following is the full entire pathname of the OOA database
  // file to be created/opened. It must begin with a "/".
  
  static Domain_id create_database( const char *p_ooa_db_full_pathname,
                                    String &p_err_msg );
  
  static Domain_id open_database( const char *p_ooa_db_full_pathname,
                                  String &p_err_msg );
  
  static t_boolean extract_names_from_path_ok( const char *p_ooa_db_full_pathname,
                                               String &p_directory,
                                               String &p_file,
                                               String &p_domain,
                                               String &p_err_msg );
  
  // ACCESS functions.
  
  Domain_id get_domain_id() const;
  String &domain_name() { return domain; }
  const char *get_domain_name_char_ptr() const
    { return domain.char_ptr(); }
  
  String &full_path_name() { return full_path; }
  const char *get_full_path_name_char_ptr() const
    { return full_path.char_ptr(); }
  
  String &directory_name() { return directory; }
  const char *get_directory_name_char_ptr() const
    { return directory.char_ptr(); }
  
  String &file_name() { return file; }
  const char *get_file_name_char_ptr() const
    { return file.char_ptr(); }

  // initial_user() is who first created this domain/database
  String &initial_user() { return _initial_user; }
  const char *get_initial_user_char_ptr() const
    { return _initial_user.char_ptr(); }
  
  // Return code of TRUE means user has write status. This status
  // incorporates factors such as personal dbs, etc.
  
  Description &domain_template() { return _template; }

  mc_dbms_database *get_db_ptr() const;

  mc_dbms_List< D_im_version_info *> *get_im_ver_coll_ptr()
    { return &im_ver_coll.getvalue(); }
  mc_dbms_List< D_sm_version_info *> *get_sm_ver_coll_ptr()
    { return &sm_ver_coll.getvalue(); }

  D_dd_version_info *get_dd_ver_info( );
  D_im_version_info *get_im_ver_info_by_id( const Id &p_id );
  D_sm_version_info *get_sm_ver_info_by_id( const Id &p_id );

  // The "current" version is the "viewed version"
  D_im_ocm_oam     *get_current_im_ocm_oam_by_id    ( const Id &p_id );
  D_sm_spt_pm      *get_current_sm_spt_pm_by_id     ( const Id &p_id );

  D_dd_srm_scm_sam *get_current_dd_srm_scm_sam_ptr() const
    { return dd_ver_ptr->get_cur_dd_ptr(); }

  void set_current_dd_srm_scm_sam( D_dd_srm_scm_sam *dd_ptr );
  void set_current_im_ocm_oam    ( D_im_ocm_oam *im_ptr );
  void set_current_sm_spt_pm     ( D_sm_spt_pm *sm_ptr );

  D_dd_srm_scm_sam *get_dd_srm_scm_sam_version_n( const Description &p_branch_name,
                                                  float ver );
  D_im_ocm_oam     *get_im_ocm_oam_version_n    ( const Id &p_id,
                                                  const Description &p_branch_name,
                                                  float ver );
  D_sm_spt_pm      *get_sm_spt_pm_version_n     ( const Id &p_id,
                                                  const Description &p_branch_name,
                                                  float ver );

  Object *find_object_by_sm_spt_pm_id( const Id &p_id );
  Object *find_object_by_id( const Id &p_id );
  Imported_object *find_imported_object_by_id( const Id &p_id );
  Relationship *find_relationship_by_id( const Id &p_id );
  D_external_entity_in_model *find_external_entity_in_model_by_id( const Id &p_id );

  Referred_to_ident_attr* find_rtida_by_id( const Id& p_attr_id,
	    const Id& p_obj_id,
	    t_uint	p_oid_id,
	    const Id& p_rel_id,
	    const Id& p_oir_id  );

  void find_all_o_ref_related_to_rtida( Referred_to_ident_attr*, 
            mc_dbms_Set< Attr_ref_in_object * >* );
  void find_all_rtida_related_to_rto( Object_referred_to*, 
            mc_dbms_List< Referred_to_ident_attr * >* );
  void find_all_o_ref_related_to_rgo( Object_referring*, 
            mc_dbms_List< Attr_ref_in_object * >* );
  
  void find_all_org_access_paths_by_id( const Id&, 
            mc_dbms_List< D_access_path * >& );
  void find_all_dest_access_paths_by_id( const Id&, 
            mc_dbms_List< D_access_path * >& );
  void find_all_org_comm_paths_by_id( const Id&, 
            mc_dbms_List< D_communication_path * >& );
  void find_all_dest_comm_paths_by_id( const Id&, 
            mc_dbms_List< D_communication_path * >& );

  D_entity* find_entity_by_id( const Id& );

  int   find_all_dangling_relationships (t_boolean p_do_all,
      mc_dbms_List<Description*> & );

  t_ulong get_domain_code () const { return domain_code; }
  void set_domain_code (t_ulong p_code) { domain_code = p_code; }

  t_ulong get_workspace_id () const { return workspace_id; }
  void set_workspace_id (t_ulong p_code) { workspace_id = p_code; }

  void set_user_rw_status();
  t_boolean get_user_rw_status();
  
  D_subsys* create_default_domain_data();

  void set_uncheckout_started( t_boolean p_started )
    { uncheckout_started = p_started; }
  t_boolean get_uncheckout_started() const { return uncheckout_started; }
  
  mc_dbms_segment *get_config_ptr()
    { return mc_dbms_segment::of( this ); }

  void create_core_data_types ();
  void create_user_data_types ();

  t_boolean update_config_data_info( const Description & p_config_data_info,
                                     String & p_err_msg );

  t_boolean update_id_assigners( GS_string & config_data_info,
                                 String & p_err_msg );

  static t_ulong get_next_workspace_id(const Domain_id &p_domain_id);
  static t_ulong get_next_config_id(const Domain_id &p_domain_id);

  D_version_tag &config_version_tag()
      { return config_ver_tag; }

private:
  
  String domain;
  String directory;
  String file;
  String full_path;
  Description _template;
  String _initial_user;
  D_version_tag config_ver_tag;
  
  t_ulong		domain_code;
  t_ulong		workspace_id;
  Id dd_id;
  t_boolean rw_status;
  t_boolean uncheckout_started;


  // HELPING functions.

  // Normally these would be invoked by User, but instead they will
  // only be invoked locally within the static create and open
  // functions.

  Domain( const char *p_full_path,
          const char *p_directory,
          const char *p_file,
          const char *p_domain );

  ~Domain();
  
  // This domain will have MANY versions of the ONE set of Models that
  // is associated with it. This pointer will be floating.

  mc_dbms_relationship_1_1(Domain,dd_ver_ptr,D_dd_version_info,m_domain_ptr,D_dd_version_info *) dd_ver_ptr;
  
  mc_dbms_relationship_m_1(Domain,im_ver_coll,D_im_version_info,m_domain_ptr,mc_dbms_List<D_im_version_info *>) im_ver_coll;

  mc_dbms_relationship_m_1(Domain,sm_ver_coll,D_sm_version_info,m_domain_ptr,mc_dbms_List<D_sm_version_info *>) sm_ver_coll;
  

};

#endif

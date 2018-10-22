/*========================================================================
 *
 * File:      $RCSfile: d_im_oam.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:14 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_IM_OCM_OAM_HH
#define D_IM_OCM_OAM_HH

//
// FILE: D_im_ocm_oam.hh   AUTHOR: David E. Solomon	CREATION DATE: 3/9/93
//
// CONTENTS: Class specification for the Information Model, Object
//	Communication Model, and Object Access Model. This class encapsulates
//	the versioning aspects of versioning these three models together.
//
// REMARKS: None.
//


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_id.hh>
#include <u_string.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_domid.hh"
#include "d_domain.hh"
#include "d_vertag.hh"
#include "d_im_ver.hh"
#include "d_imasnr.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class D_im_ocm_oam;

// Also declare classes in other subsystems(generic) that we reference, but
// don't need header file.

class Subsystem;
class Object;
class Imported_object;
class Relationship;
class Attribute;

class D_subsys;
class D_external_entity_in_model;
class D_access_path;
class D_communication_path;

class Simple_relationship;
class Associative_relationship;
class Inheritance_relationship;
class Composition_relationship;

class M_im;
class M_ocm;
class M_oam;


//
// CLASS: D_im_ocm_oam
//
// DESCRIPTION: Define the class that defines the versioned models associated
//	with a specific Subsystem.
//
// REMARKS: None.
//

class D_im_ocm_oam
{
public:
  // MANAGER functions

  static mc_dbms_typespec *get_mc_dbms_typespec();
  mc_dbms_segment* get_config_ptr () const { return mc_dbms_segment::of (this); }
  mc_dbms_database *get_db_ptr() const { return get_domain_ptr()->get_db_ptr(); }

  // IMPLEMENTOR functions

  enum cross_comp_rels_e {
       R9,
       R101, R109, R110, R111_RTIDA, R111_RGO, R114, R116, R118,
       R201,
       R403, R405, R406, R407, R409, R410, R413, R414, R416, R417, R419, R420, R424, R425,
       R524, R527, R528
       };

  int find_all_dangling_relationships ( t_boolean p_do_ca_tests,
                      t_boolean p_do_sm_tests, t_boolean p_do_dt_tests,
                      mc_dbms_List<Description*> &p_dangle_list,
                      const Description& p_domain_name, 
                      const Description& p_subsys_name,
                      e_diagram_display_mode dm );

  // Version Management functions.
  
  // !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
  // The following version management functions require that the
  // caller had better NOT be in a transaction.
  
  static t_boolean checkout_im_ocm_oam( const Domain_id &p_domain_id,
                                        const Id &p_im_ocm_oam_id,
                                        const t_boolean p_end_branch,
                                        const t_boolean p_reserved,
                                        const Description &p_target_branch_name,
                                        String &p_err_msg );
  
  static t_boolean uncheckout_im_ocm_oam( const Domain_id &p_domain_id,
                                          const Id &p_im_ocm_oam_id,
                                          String &p_err_msg );
  
  static t_boolean browse_im_ocm_oam( const Domain_id &p_domain_id,
                                      const Id &p_im_ocm_oam_id,
                                      String &p_err_msg,
                                      const Description &p_branch_name,
                                      const float p_origin_version_num );
  
  static t_boolean checkin_im_ocm_oam( const Domain_id &p_domain_id,
                                       const Id &p_im_ocm_oam_id,
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
                           const Id &p_im_ocm_oam_id,
                           Description &p_config_data_info );
  

  // !!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // The following version management functions require that the
  // caller had BETTER be in a transaction.
  
  static t_boolean is_ok_to_delete( const Domain_id &p_domain_id,
                                    const Id &p_im_ocm_oam_id,
                                    String &p_err_msg,
                                    const Description &p_branch_name,
                                    float p_version_num );
  
  static t_boolean is_checked_out( const Domain_id &p_domain_id,
                                   const Id &p_im_ocm_oam_id,
                                   D_version_tag &p_version_tag );

  static t_boolean is_checked_out_by_me( const Domain_id &p_domain_id,
                                         const Id &p_im_ocm_oam_id );

  t_boolean is_checked_out();
  
  t_boolean is_checked_out_by_me();

  t_boolean is_first_version();
  t_boolean is_last_version();
  t_boolean is_branch_version();

  D_im_version_info *get_ver_ptr() const
    { return m_im_ver_ptr; }

  // CREATION functions

  // Create a new subsystem model (configuration).  It will be version 1.0
  // and marked as checked in.
  static Id create_new_subsystem_model ( Domain *p_domain_ptr,
                                         const Id & p_dd_subsystem_id,
                                         t_uint p_config_id,
                                         const Description &p_branch_name,
                                         t_ulong p_version_num );
  
  // Create a version of an existing subsystem model (configuration).
  static D_im_ocm_oam *create_subsystem_model ( Domain *p_domain_ptr,
                                                const Id & p_im_id,
                                                const Description &p_branch_name,
                                                float p_version_num );

  // DELETION functions

  // Delete the current version
  t_boolean destroy_im_version( String &p_err_msg);
  void delete_im_ocm_oam();
  ~D_im_ocm_oam();

  // MISCELLANEOUS access functions

  D_version_tag &version_tag()
      { return ver_tag; }

  t_boolean is_viewed_version() const
      { return (this == get_ver_ptr()->get_cur_im_ptr())? TRUE: FALSE; }

  D_im_assigners *get_assigners()
    { return assigners; }

  // Related MODEL functions

  M_im *get_M_im_ptr() const { return m_M_im_ptr; }
  M_ocm *get_M_ocm_ptr() const { return m_M_ocm_ptr; }
  M_oam *get_M_oam_ptr() const { return m_M_oam_ptr; }
  
  // ITERATOR and FIND/QUERY functions.


  Object *create_object(const vchar *p_name = Description::null_string,
                        t_uint p_number = 0,
                        const vchar *p_key_letters = Description::null_string,
                        const Description & p_description =
                        Description::Default );

  Object *create_object(const Id & p_id,
                        const vchar *p_name = Description::null_string,
                        t_uint p_number = 0,
                        const vchar *p_key_letters = Description::null_string,
                        const Description & p_description =
                        Description::Default );

  Imported_object *create_imported_object( const Id &p_origin_obj_id );

  Imported_object *create_imported_object( const Id &p_origin_obj_id,
                                           const Id &p_imp_obj_id );

  Simple_relationship *create_simple_relationship( Id p_id,
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Simple_relationship *create_simple_relationship(
			t_uint p_rel_num = 0, 
            const Description & p_description = Description::Default );

  Associative_relationship *create_associative_relationship( Id p_id,
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Associative_relationship *create_associative_relationship(
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Inheritance_relationship *create_inheritance_relationship( Id p_id,
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Inheritance_relationship *create_inheritance_relationship(
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Composition_relationship *create_composition_relationship( Id p_id,
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  Composition_relationship *create_composition_relationship(
		t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

  void delete_object( Object *p_object_ptr );
  void delete_object_and_its_relationships( Object *p_object_ptr );

  void delete_relationship( Relationship *p_rel_ptr );

  t_uint get_number_of_objects();
  t_uint get_number_of_relationships();
  t_uint get_number_of_external_entity_in_models()
      { return external_entity_in_model_coll.cardinality(); }

  t_boolean verify_all_imported_objects_rw( Description& );

  // find/query functions.

  Object *find_object_by_id( const Id &p_id );
  Object *find_object_by_name( const vchar *p_name );
  Object *find_object_by_kl( const Description& p_name );

  Imported_object *find_imported_object_by_id( const Id &p_id );

  Relationship *find_relationship_by_id( const Id &p_id );
  Relationship *find_relationship_by_number( t_uint p_number );

  Attribute *find_attribute_by_id( const Id &p_id );

  D_access_path *find_access_path_by_id( const Id &p_id );
  D_communication_path *find_communication_path_by_id(const Id &p_id );

  D_external_entity_in_model *find_external_entity_in_model_by_id(
	    	const Id &p_id );

  long repair_referential_attributes ();

  // ACCESS functions.

  const Id & get_id() const { return id; }
  t_uint get_config_id() const { return get_id().get_config_id(); }
  Domain *get_domain_ptr() const { return get_ver_ptr()->get_domain_ptr(); }
  Domain_id get_domain_id() const { return get_domain_ptr()->get_domain_id(); }

  Subsystem *get_im_subsystem_ptr() const
      { return subsystem_ptr; }
  D_subsys *get_dd_subsystem_ptr() const;
  
  D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr() const;

  mc_dbms_List< Object * > *get_object_coll_ptr()
      { return &objects.getvalue(); }
  mc_dbms_List< Attribute * > *get_attr_coll_ptr()
      { return &attributes.getvalue(); }
  mc_dbms_List< Imported_object * > *get_imported_obj_coll_ptr()
      { return &imported_objects.getvalue(); }
  mc_dbms_List< Relationship * > *get_rel_coll_ptr()
      { return &relationships.getvalue(); }
  mc_dbms_List< D_access_path * > *get_access_path_coll_ptr()
      { return &access_path_coll.getvalue(); }
  mc_dbms_List< D_communication_path * > *get_comm_path_coll_ptr()
      { return &comm_path_coll.getvalue(); }
  mc_dbms_List< D_external_entity_in_model * > *
    get_external_entity_in_model_coll_ptr()
      { return &external_entity_in_model_coll.getvalue(); }
  mc_dbms_List< Attr_ref_in_object * > *
    get_attr_ref_in_obj_coll_ptr()
      { return &attr_ref_in_objects.getvalue(); }

  DELETE_DOWN_DECL_SUBTYPE()


private:
  Id id;
  D_version_tag ver_tag;
  D_im_assigners *assigners;

  // HELPING functions
  
  t_boolean update_id_assigners( GS_string & p_id_assigner_info,
                                 String & p_err_msg );

  void delete_objects();
  void delete_imported_objects() {}
  void delete_relationships();

  D_im_ocm_oam( D_im_version_info *im_ver_ptr,
                const Id & p_dd_subsystem_id,
                t_uint config_id,
                const Description &p_branch_name,
                t_ulong p_version_num );
  
  // Maintain collection of Objects
  
  mc_dbms_relationship_1_m(D_im_ocm_oam,m_im_ver_ptr,D_im_version_info,m_im_ocm_oam_ver_coll,D_im_version_info *) m_im_ver_ptr;

  mc_dbms_relationship_m_1(D_im_ocm_oam,objects,Object,im_ocm_oam_ptr,mc_dbms_List< Object * >) objects;

  mc_dbms_relationship_m_1(D_im_ocm_oam,imported_objects,Imported_object,im_ocm_oam_ptr,mc_dbms_List< Imported_object * >) imported_objects;

  mc_dbms_relationship_m_1(D_im_ocm_oam,attributes,Attribute,im_ocm_oam_ptr,mc_dbms_List< Attribute * >) attributes;

  // Maintain collection of Relationships

  mc_dbms_relationship_m_1(D_im_ocm_oam,relationships,Relationship,im_ocm_oam_ptr,mc_dbms_List< Relationship * >) relationships;
  
  mc_dbms_relationship_m_1(D_im_ocm_oam,access_path_coll,D_access_path,im_ocm_oam_ptr,mc_dbms_List< D_access_path * >) access_path_coll;

  mc_dbms_relationship_m_1(D_im_ocm_oam,comm_path_coll,D_communication_path,im_ocm_oam_ptr,mc_dbms_List< D_communication_path * >) comm_path_coll;

  mc_dbms_relationship_m_1(D_im_ocm_oam,external_entity_in_model_coll,D_external_entity_in_model,im_ocm_oam_ptr,mc_dbms_List< D_external_entity_in_model * >) external_entity_in_model_coll;

  mc_dbms_relationship_1_1(D_im_ocm_oam,subsystem_ptr,Subsystem,im_ocm_oam_ptr,Subsystem *) subsystem_ptr;
  
  mc_dbms_relationship_1_1(D_im_ocm_oam,m_M_im_ptr,M_im,im_ocm_oam_ptr,M_im *) m_M_im_ptr;

  mc_dbms_relationship_1_1(D_im_ocm_oam,m_M_ocm_ptr,M_ocm,im_ocm_oam_ptr,M_ocm *) m_M_ocm_ptr;

  mc_dbms_relationship_1_1(D_im_ocm_oam,m_M_oam_ptr,M_oam,im_ocm_oam_ptr,M_oam *) m_M_oam_ptr;

  mc_dbms_relationship_m_1(D_im_ocm_oam,attr_ref_in_objects,Attr_ref_in_object,im_ocm_oam_ptr,mc_dbms_List< Attr_ref_in_object * >) attr_ref_in_objects;

};


#endif /* D_IM_OCM_OAM_HH */

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//

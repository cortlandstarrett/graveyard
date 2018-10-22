/*========================================================================
 *
 * File:      $RCSfile: d_subsys.hh,v $
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

#ifndef D_SUBSYS_HH
#define D_SUBSYS_HH

//
// FILE: D_subsystem.hh	AUTHOR: David E. Solomon	CREATION DATE: 11/6/92
//
// CONTENTS:
//
//		This file describes the C++ classes relating to an OOA Subsystem.
//
// REMARKS:
//
//		A subsystem is a logical breakdown or partitioning of the Objects
//		in a given OOA Domain. In this regard, a given Subsystem will belong
//		to one and only one Domain and will contain many Objects. An Object
//		will be owned by one and only one Subsystem. However, a Subsystem
//		may refer to other Objects that are owned by other Subsystems in
//		that same domain only.
//
//		By S/M OOA definition, a given Subsystem never refers to any
//		other Domains in any way.
//		


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_string.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_domid.hh"
#include "d_dd_sam.hh"
#include "d_im_oam.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class D_subsys;

// Also declare classes in other subsystems(generic) that we reference, but
// don't need header file.

class Domain;
class D_dd_srm_scm_sam;

//
// CLASS: D_subsys
//
// DESCRIPTION:
//
//		This defines the basic OOA Subsystem.
//
// REMARKS:
//
//		A D_subsys belongs to one and only one domain and contains/owns
//		many Objects. For versioning purposes, a given D_subsys can be
//		associated with only ONE D_dd_srm_scm_sam instance. However, a
//		given D_subsys will be versioned via the D_im_ocm_oam class.
//

class D_subsys
{
public:
  // MANAGER functions

  static mc_dbms_typespec *get_mc_dbms_typespec();

  D_subsys( D_dd_srm_scm_sam *p_dd_ptr,
            const Description &p_name,
            t_uint p_config_id,
            const Description &p_target_branch_name,
            float p_version_num );
  D_subsys( D_dd_srm_scm_sam *p_dd_ptr,
            const Description &p_name,
			const Id & p_id,
            t_uint p_config_id,
            const Description &p_target_branch_name,
            float p_version_num );
  D_subsys( D_dd_srm_scm_sam *p_dd_ptr,
            const Description &p_name,
			const Id & p_im_id );
  
  // This constructor is for an orphaned subsystem.

  D_subsys( const vchar *p_name );

  ~D_subsys();

  static void init();

  // IMPLEMENTOR functions

  void export();

  // ACCESS functions.

  const Id & get_subsystem_id() { return id; }
  const Id & get_id() { return id; }
  Description get_subsystem_name() const { return name; }
  const vchar *get_subsystem_name_char_ptr() const
      { return name.char_ptr(); }
  void set_subsystem_name( const vchar *p_name );
  Description &description() { return desc; }
  Description &key_letters() { return _key_letters; }
  
  t_uint get_obj_rel_num_range_lo() const
      { return obj_rel_num_range_lo; }
  void set_obj_rel_num_range_lo( t_uint range_lo )
      { obj_rel_num_range_lo = range_lo; }

  static D_subsys *get_orphaned_subsystem_ptr()
      { return orphaned_subsystem_ptr; }
  t_boolean is_orphaned() const
      { return( this == orphaned_subsystem_ptr ? TRUE : FALSE ); }


  D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr() const
      { return dd_srm_scm_sam_ptr; }

  Domain *get_domain_ptr() const
      { return get_dd_srm_scm_sam_ptr()->get_domain_ptr(); }
  mc_dbms_database *get_db_ptr() const
      { return get_dd_srm_scm_sam_ptr()->get_db_ptr(); }

  Object*  find_object_in_other_subsys( const Description& name, 
                const Description& kl );

  // IM junk

  D_im_ocm_oam *get_im_ocm_oam_ptr() const;
  const Id &get_im_ocm_oam_id() const { return im_id; }

  mc_dbms_segment* get_config_ptr ()
      { return mc_dbms_segment::of (this); }

  DELETE_DOWN_DECL_SUBTYPE()

private:

  Id id;
  Description name;
  Description desc;
  Description _key_letters;
  t_uint obj_rel_num_range_lo;

  Id im_id;
      
  static D_subsys *orphaned_subsystem_ptr;
      
  // HELPING functions

  Id_assigner &id_assigner()
      { return get_dd_srm_scm_sam_ptr()->get_assigners()->subsystem_id_assigner(); }

  Id assign_id()
      { return ( id_assigner().assign_next_id() ); }

  mc_dbms_relationship_1_m(D_subsys,dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,subsystem_dd_coll,D_dd_srm_scm_sam *) dd_srm_scm_sam_ptr;

	};

#endif

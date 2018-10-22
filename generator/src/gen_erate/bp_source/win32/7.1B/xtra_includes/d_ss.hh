/*========================================================================
 *
 * File:      $RCSfile: d_ss.hh,v $
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

#ifndef D_SS_HH
#define D_SS_HH

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
#include "d_im_oam.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Subsystem;

// Also declare classes in other subsystems(generic) that we reference, but
// don't need header file.

class Domain;


//
// CLASS: Subsystem
//
// DESCRIPTION:
//
//		This defines the basic OOA Subsystem.
//
// REMARKS:
//
//		A Subsystem belongs to one and only one domain and contains/owns
//		many Objects. For versioning purposes, a given Subsystem can be
//		associated with only ONE D_dd_srm_scm_sam instance. However, a
//		given Subsystem will be versioned via the D_im_ocm_oam class.
//

class Subsystem
{
public:
  // MANAGER functions
  
  static mc_dbms_typespec *get_mc_dbms_typespec();

  Subsystem( D_im_ocm_oam *p_im_ptr,
             const Id & p_dd_subsystem_id );
  Subsystem( D_im_ocm_oam *p_im_ptr,
             const Id & p_dd_subsystem_id,
             const Id & p_id );

  ~Subsystem();

  // IMPLEMENTOR functions

  // ACCESS functions.

  const Id & get_id() const
    { return id; }

  D_im_ocm_oam *get_im_ocm_oam_ptr() const
    { return im_ocm_oam_ptr; }

  const Id &get_im_ocm_oam_id() const
    { return get_im_ocm_oam_ptr()->get_id(); }

  Domain *get_domain_ptr() const
    { return get_im_ocm_oam_ptr()->get_domain_ptr(); }

  D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr() const
    { return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr(); }

  const Id &get_dd_subsystem_id()
    { return dd_subsystem_id; }

  mc_dbms_segment* get_config_ptr ()
    { return mc_dbms_segment::of(this); }

private:

  Id id;
  Id dd_subsystem_id;

  mc_dbms_relationship_1_1(Subsystem,im_ocm_oam_ptr,D_im_ocm_oam,subsystem_ptr,D_im_ocm_oam *) im_ocm_oam_ptr;

};

#endif

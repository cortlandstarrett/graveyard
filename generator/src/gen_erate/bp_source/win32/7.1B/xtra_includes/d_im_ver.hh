/*========================================================================
 *
 * File:      $RCSfile: d_im_ver.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:12 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_IM_VERSION_INFO_HH
#define D_IM_VERSION_INFO_HH

//
// FILE: D_im_version_info.hh   AUTHOR: David E. Solomon  CREATION DATE: 8/4/93
//
// CONTENTS:
//
// REMARKS:
//


// Include those header files that are DIRECTLY needed by this one.



#include "u_typdef.hh"
#include "u_id.hh"
#include "u_desc.hh"

#include "d_typdef.hh"


// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class D_im_version_info;
class Domain;
class D_im_ocm_oam;

// Also declare classes in other subsystem that we reference, but don't
// include header file.


//
// CLASS: D_im_version_info
//
// DESCRIPTION: Maintain version status information for what version is
//	current for each state model.
//
// REMARKS: None.
//

class D_im_version_info
{
public:
  static mc_dbms_typespec* get_mc_dbms_typespec ();
  
  ~D_im_version_info()
      {}

  const Id &get_id() const { return im_id; }

  Domain *get_domain_ptr() { return m_domain_ptr; }
  
  void set_cur_im_ptr( D_im_ocm_oam *p_im_ptr ) { cur_im_ptr = p_im_ptr; }
  D_im_ocm_oam *get_cur_im_ptr() const { return cur_im_ptr; }

  float get_cur_im_ver_num() const;

  D_im_ocm_oam *get_im_version_n( const Description &p_branch_name,
                                  const float p_version_num );

  mc_dbms_List<D_im_ocm_oam *> *get_im_coll_ptr ()
    { return &(m_im_ocm_oam_ver_coll.getvalue ()); }

  D_im_ocm_oam *get_last_im_version(const Description &p_branch_name);
  D_im_ocm_oam *get_last_nonbranch_im_version(const Description &p_branch_name);

  D_im_ocm_oam *get_previous_im_version(D_im_ocm_oam *ref_im_ptr);

  static D_im_version_info *get_im_info(Domain *p_domain_ptr,
                                        const Id &p_id);
  static D_im_version_info *create_im_info(Domain *p_domain_ptr,
                                           const Id &p_id);
private:
  Id im_id;
  D_im_ocm_oam *cur_im_ptr;

  D_im_version_info(Domain *p_domain_ptr,
                    const Id &p_id);
  
  mc_dbms_relationship_1_m(D_im_version_info,m_domain_ptr,Domain,im_ver_coll,Domain*) m_domain_ptr;
  
  mc_dbms_relationship_m_1(D_im_version_info,m_im_ocm_oam_ver_coll,D_im_ocm_oam,m_im_ver_ptr,mc_dbms_List<D_im_ocm_oam*>) m_im_ocm_oam_ver_coll;
};


#endif /* D_IM_VERSION_INFO_HH */

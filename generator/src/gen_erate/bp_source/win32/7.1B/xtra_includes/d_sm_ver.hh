/*========================================================================
 *
 * File:      $RCSfile: d_sm_ver.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:08 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_SM_VERSION_INFO_HH
#define D_SM_VERSION_INFO_HH

//
// FILE: D_sm_version_info.hh   AUTHOR: David E. Solomon  CREATION DATE: 8/4/93
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

class D_sm_version_info;
class Domain;
class D_sm_spt_pm;

// Also declare classes in other subsystem that we reference, but don't
// include header file.


//
// CLASS: D_sm_version_info
//
// DESCRIPTION: Maintain version status information for what version is
//	current for each state model.
//
// REMARKS: None.
//

class D_sm_version_info
{
public:
  static mc_dbms_typespec* get_mc_dbms_typespec ();
  
  ~D_sm_version_info()
      {}
  
  const Id &get_id() const { return sm_id; }

  Domain *get_domain_ptr() { return m_domain_ptr; }
  
  void set_cur_sm_ptr( D_sm_spt_pm *p_sm_ptr ) { cur_sm_ptr = p_sm_ptr; }
  D_sm_spt_pm *get_cur_sm_ptr() const { return cur_sm_ptr; }

  float get_cur_sm_ver_num() const;

  D_sm_spt_pm *get_sm_version_n( const Description &p_branch_name,
                                 const float p_version_num );

  mc_dbms_List<D_sm_spt_pm *> *get_sm_coll_ptr ()
    { return &(m_sm_spt_pm_ver_coll.getvalue ()); }

  D_sm_spt_pm *get_last_sm_version(const Description &p_branch_name);
  D_sm_spt_pm *get_last_nonbranch_sm_version(const Description &p_branch_name);

  D_sm_spt_pm *get_previous_sm_version(D_sm_spt_pm *ref_sm_ptr);

  static D_sm_version_info *get_sm_info(Domain *p_domain_ptr,
                                        const Id &p_id);
  static D_sm_version_info *create_sm_info(Domain *p_domain_ptr,
                                           const Id &p_id);
private:
  Id sm_id;
  D_sm_spt_pm *cur_sm_ptr;
  
  D_sm_version_info(Domain *p_domain_ptr,
                    const Id &p_id);
  
  mc_dbms_relationship_1_m(D_sm_version_info,m_domain_ptr,Domain,sm_ver_coll,Domain*) m_domain_ptr;
  
  mc_dbms_relationship_m_1(D_sm_version_info,m_sm_spt_pm_ver_coll,D_sm_spt_pm,m_sm_ver_ptr,mc_dbms_List<D_sm_spt_pm*>) m_sm_spt_pm_ver_coll;
};


#endif /* D_SM_VERSION_INFO_HH */

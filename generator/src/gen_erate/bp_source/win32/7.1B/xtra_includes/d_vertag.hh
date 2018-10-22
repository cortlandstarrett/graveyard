/*========================================================================
 *
 * File:      $RCSfile: d_vertag.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef D_VERTAG_HH
#define D_VERTAG_HH

//
// FILE: D_version_tag.hh	AUTHOR: David E. Solomon	CREATION DATE: 3/4/93
//
// CONTENTS: Class that defines what constitutes the identification tag of a
// 	checked-out version.
//
// REMARKS: None.
//


// Include those header files that are DIRECTLY needed by this one.

#include <time.h>

#include "u_typdef.hh"

#include "u_string.hh"
#include "u_desc.hh"


// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class D_version_tag;


// Declare classes that we only need a pointer to.



//
// CLASS: D_version_tag
//
// DESCRIPTION: Define version tag that we associate with any versioned
//	persistent object.
//
// REMARKS: This object will contain different fields that may be useful in
//	identifying (ie - tagging) a version.
//

class D_version_tag
{
public:
  // MANAGER functions

  static mc_dbms_typespec *get_mc_dbms_typespec();

  D_version_tag(const Description &p_branch_name,
                t_ulong p_version_num);

  D_version_tag() {}
  ~D_version_tag() {}

  // IMPLEMENTOR functions

  void check_in(const Description &p_new_branch_name,
                const t_ulong p_new_version_num,
                const t_boolean p_pinned);

  void check_out(const t_boolean p_end_branch,
                 const t_boolean p_reserved,
                 const Description &p_target_branch_name);

  void set_pre_checkout_info(const Description &p_original_branch_name,
                             const t_ulong p_original_version_num,
                             const t_boolean p_original_pinned);

  void un_check_out();
  void unreserve();
  
  static const char *convert_to_mc_dbms_ver_num( float p_ver_num );
  static const char *get_version_num_as_string (float p_ver_num);

  // ACCESS functions.

  t_boolean is_checked_out()       const
    { if (checkout_status == NOT_CHECKED_OUT) return FALSE; return TRUE; }
  const Description &get_current_branch_name ()
                                   const { return current_branch_name; }
  void set_current_branch_name (const Description &p_branch_name)
                                         { current_branch_name = p_branch_name; }
  float get_current_version_num()  const { return current_version_num; }
  void set_current_version_num( float p_ver_num )
                                         { current_version_num = p_ver_num; }
  const char *get_version_num_as_string () const;

  const Description &get_original_branch_name ()
                                   const { return original_branch_name; }
  float get_original_version_num() const { return original_version_num; }
  t_boolean is_original_pinned()   const { return original_pinned; }


  const Description &get_target_branch_name ()
                                   const { return target_branch_name; }
  t_boolean is_end_branch()        const { return end_branch; }
  t_boolean is_reserved()          const { return reserved; }
  t_boolean is_pinned()            const { return pinned; }
  void set_pinned(t_boolean p_pinned)    { pinned = p_pinned; }

  const String &get_co_user_name() const { return co_user_name; }
  const time_t &get_co_gmt_secs()  const { return co_gmt_secs; }
  const String &get_co_date_time() const { return co_date_time; }
  const Description &get_previous_branch_name ()
                                   const { return previous_branch_name; }
  float get_previous_version_num() const { return previous_version_num; }
  const String &get_ci_user_name() const { return ci_user_name; }
  const time_t &get_ci_gmt_secs()  const { return ci_gmt_secs; }
  const String &get_ci_date_time() const { return ci_date_time; }

private:
  enum t_checkout_status
  {
    NOT_CHECKED_OUT,
    CHECKED_OUT_UNRESERVED,
    CHECKED_OUT_RESERVED
  };
  t_checkout_status checkout_status;

  Description current_branch_name;
  float current_version_num;
  t_boolean pinned;

  // Checked-out information
  Description target_branch_name;
  t_boolean end_branch;
  t_boolean reserved;
  String co_user_name;
  time_t co_gmt_secs;
  String co_date_time;

  // Pre-checkout information
  Description original_branch_name;
  float original_version_num;
  t_boolean original_pinned;

  // Checked-in information
  Description previous_branch_name;
  float previous_version_num;
  String ci_user_name;
  time_t ci_gmt_secs;
  String ci_date_time;
};

#endif /* D_VERTAG_HH */

/*========================================================================
 *
 * File:      $RCSfile: d_sm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_sm_HH
#define D_sm_HH




#include <d_domain.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_moore_sm;
class D_mealy_sm;



class D_sm
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_sm (Domain*, D_sm_spt_pm*);

    virtual ~D_sm ();



    //  IMPLEMENTOR functions
    //

    void delete_sm ();
    void copy_sm (D_sm_spt_pm*);
    void paste_sm (t_uint);



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr = p_sm_spt_pm_ptr; }

    virtual D_moore_sm* get_moore_sm_ptr ()
        { return 0; }

    virtual D_mealy_sm* get_mealy_sm_ptr ()
        { return 0; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUPERTYPE()


private:

    mc_dbms_relationship_1_1(D_sm,m_sm_spt_pm_ptr,D_sm_spt_pm,m_sm_ptr,D_sm_spt_pm*) m_sm_spt_pm_ptr;
};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

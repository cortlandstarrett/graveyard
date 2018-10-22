/*========================================================================
 *
 * File:      $RCSfile: gs_actn.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_ACTN_HH
#define GS_ACTN_HH


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif

#include <u_string.hh>




class GS_action

{
public:
    enum e_action_home	{
			NONE,
			ASSIGNER_STATE,
			ATTRIBUTE,
			BRIDGE,
			DATA_TYPE,
			EE_EVENT,
			INSTANCE_STATE,
			RELATIONSHIP,
			SM_EVENT,
			TRANSFORMER,
			SYNCH_SERVICE
			};




protected:
			GS_action (const GS_string& p_action_str)
			    : m_action_str (p_action_str) {}
    virtual		~GS_action () {}

    GS_string		uncomment_action ();

    t_boolean		get_next_stmt ();

    GS_string		m_action_str;




private:
};




#endif

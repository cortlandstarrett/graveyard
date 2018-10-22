/*========================================================================
 *
 * File:      $RCSfile: i_idb.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef I_IDB_HH
#define I_IDB_HH

#include <u_typdef.hh>
#include <u_string.hh>


class mc_dbms_database;
class GS_string;


const int NUM_DOMAIN_CODES = 16;
const int DOMAIN_CODE_AVAILABLE = 0;
const int DOMAIN_CODE_USED = 1;


class I_instance_db
{
public:
    static t_boolean	domain_code_ok
			    (mc_dbms_database* p_db_ptr,
			    int p_entered_domain_code,
				int &p_chosen_domain_code,
			    String &p_err_msg);

    static t_ulong	get_sim_domain_code (mc_dbms_database* p_db_ptr);
    static void		set_sim_domain_code
			    (mc_dbms_database* p_db_ptr, t_ulong p_domain_code);


private:
};




#endif

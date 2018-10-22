/*========================================================================
 *
 * File:      $RCSfile: u_date.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef		U_DATE_HH
#define		U_DATE_HH


#include <u_typdef.hh>
#include <u_desc.hh>




class RM_date

{
public:
			RM_date () {};
    virtual		~RM_date () {};
			

    static t_ulong	get_current_time_in_milliseconds ();
    static Description	get_current_time_as_string ();

	


private:
};




#endif	

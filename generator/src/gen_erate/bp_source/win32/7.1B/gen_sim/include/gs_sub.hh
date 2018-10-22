/*========================================================================
 *
 * File:      $RCSfile: gs_sub.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_SUB_HH
#define GS_SUB_HH

#include <u_string.hh>


class Description;

class GS_substitution

{
public:
    static Description&	substitute_string (const Description& p_in_str,
			    t_boolean p_is_literal_text_line);

    static void *translate_parm;

};




#endif

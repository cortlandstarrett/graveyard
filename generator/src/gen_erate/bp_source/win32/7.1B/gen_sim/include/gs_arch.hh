/*========================================================================
 *
 * File:      $RCSfile: gs_arch.hh,v $
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
#ifndef GS_ARCH_H
#define GS_ARCH_H


#include <iostream.h>

#include <gs_sizes.hh>
#include <u_string.hh>



class GS_archetype
{
public:
    static t_boolean	populate_archetype
			    (const GS_string& p_arch_file_name_str,
                            long p_number_of_populations,
			    const GS_string& p_gen_file_name_str);
    static streampos    get_char_num ();

    static t_boolean	test_open_arch_file
			    (const GS_string& p_arch_file_name_str);

    static GS_string    populate_string (GS_string& p_in_str,
			    t_boolean p_is_literal_text_line = TRUE);

    static void script_changed( const GS_string& p_script_file_name );  // i3159.2.1 added

protected:
    


private:
    static t_boolean    open_arch_file
			    (const GS_string& p_arch_file_name_str);
    static t_boolean    goto_arch_file_line (streampos p_char_num,
			    unsigned int p_line_num,
                            const GS_string& p_arch_file_name_str
				= GS_string__NULL);
    static void         close_arch_file ();
    static t_boolean    get_next_line ();

    static void         for_fast_forward_to_end ();
    static void         while_fast_forward_to_end ();
    static void         if_fast_forward ();
    static void         if_fast_forward_to_end ();
};




#endif

/*========================================================================
 *
 * File:      $RCSfile: gs_imp.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_IMP_HH
#define GS_IMP_HH

#include <u_typdef.hh>
#include <gs_sizes.hh>

class Description;
class ifstream;

class GS_import
{
public:
    static t_boolean	import_sql_file (istream* p_stream_ptr);


private:
    static void		print_create_table_usage ();
    static void		print_create_rop_ref_id_usage ();
    static void		print_create_rop_chain_usage ();
    static void		print_insert_usage ();

    static t_boolean	increment_cursor
			    (Description& p_curr_sql_stmt_str,
				t_uint& p_curr_sql_stmt_cursor,
			    istream* p_stream_ptr,
                            t_boolean p_ignore_comments);
    static t_boolean	import_sql_statement (const Description& p_stmt_str);
};




#endif
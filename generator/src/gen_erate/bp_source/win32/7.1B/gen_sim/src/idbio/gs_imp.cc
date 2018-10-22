/*========================================================================
 *
 * File:      $RCSfile: gs_imp.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:42:22 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include <time.h>

#include <u_trace.hh>
#include <u_error.hh>
#include <u_cursor.hh>
#include <u_file.hh>

#include <gs_imp.hh>
#include <gs_ui.hh>
#include <u_string.hh>
#include <u_desc.hh>

#include <i_var.hh>

#include <i_obj.hh>
#include <i_attr.hh>
#include <i_rel.hh>

#include <i_oinst.hh>
#include <i_ainst.hh>
#include <i_rop.hh>
#include <i_idaref.hh>
#include <i_roip.hh>
#include <i_ir_rop.hh>
#include <i_c_rop.hh>

using namespace std;

                               
extern mc_dbms_database* GS_gen_sim_db_ptr;


void
GS_import::print_create_table_usage ()

{
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("\n")
	+ "Syntax of 'CREATE TABLE' command incorrect - correct syntax is:\n"
	+ "    CREATE  TABLE  <obj>  (<attr> <type>,...)\n"
	+ "    where  <type>  can be  BOOLEAN, INTEGER, REAL, STRING, or UNIQUE_ID.\n\n");
}





void
GS_import::print_create_rop_ref_id_usage ()

{
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("\n")
	+ "Syntax of 'CREATE ROP REF_ID' command incorrect - correct syntax is:\n"
	+ "    CREATE  ROP  REF_ID  <rel_#>  FROM  <mult-cond> <obj> (<ref_attr>,...)\n"
	+ "                                  [ PHRASE '<from-rel-phrase>' ]"
	+ "                                  TO    <mult-cond> <obj> (<id_attr>,...)\n\n"
	+ "                                  [ PHRASE '<to-rel-phrase>' ]");
}





void
GS_import::print_create_rop_chain_usage ()

{
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("\n")
	+ "Syntax of 'CREATE ROP CHAIN' command incorrect - correct syntax is:\n"
	+ "    CREATE  ROP  CHAIN  <rel_#> FROM  <mult-cond> <obj>\n"
	+ "                                  [ PHRASE '<from-rel-phrase>' ]"
	+ "                                  TO  <mult-cond> <obj>\n"
	+ "                                  [ PHRASE '<to-rel-phrase>' ]"
	+ "                             THROUGH  <chain>\n\n");
}





void
GS_import::print_insert_usage ()

{
    GS_ui::inform (UI_INFORM__ERROR, GS_string ("\n")
	+ "Syntax of 'INSERT' command incorrect - correct syntax is:\n"
	+ "    INSERT  INTO  <obj>  VALUES  (<value>,...)");
}





t_boolean
GS_import::increment_cursor
    (Description& p_curr_sql_stmt_str, t_uint& p_curr_sql_stmt_cursor, 
	::istream*  p_stream_ptr, t_boolean p_ignore_comments)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
      "Begin  GS_import::increment_cursor (). stmt_str: '%s'",
    p_curr_sql_stmt_str.char_ptr() + p_curr_sql_stmt_cursor ));

    if (p_curr_sql_stmt_cursor >= p_curr_sql_stmt_str.length ())
    {
	LOG_ERROR ((L_log_string,
	    "GS_import::increment_cursor ():  cursor >= length - going on with execution anyway..."));
    }

	
    while (p_curr_sql_stmt_cursor >= (p_curr_sql_stmt_str.length () - 1))
    {
		//  Get line from file - sift out any comment lines...
		//
		Description line (8192);
		char system_line[8192];
		vchar system_line_vchar[8192];
		t_boolean line_is_comment = TRUE;
		do
		{
			p_stream_ptr->getline (system_line, 8192);
			GS_ui::increment_line_num ();
			if (!p_stream_ptr->good())
			{
				return FALSE;
			}

			vcharCopyScribed(vcharScribeSystem(system_line), 
				system_line_vchar);
            line = system_line_vchar;
			if ( !p_ignore_comments )
			{
				if (! ((line.length () > 1)
					&& (line.char_at(0) == '-') && (line.char_at(1) == '-')))
				{
					line_is_comment = FALSE;
				}
			}
			else
			{
				line_is_comment = FALSE;
			}
		}
		while (line_is_comment);

		p_curr_sql_stmt_str += line;
		p_curr_sql_stmt_str.append_char('\n');
    }
	
    p_curr_sql_stmt_cursor++;
	
    return TRUE;
}





t_boolean
GS_import::import_sql_file (::istream *  p_stream_ptr)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_import::import_sql_file (p_stream_ptr=0x%08x).",
	p_stream_ptr));


    GS_ui::reset_line_num ();


    //  Declare variable for the current and next sql statement.  Need to
    //    'prime' the curr_sql_stmt_str with some white space so that the
    //    increment cursor function works properly.
    //
    Description curr_sql_stmt_str ("  ");
	t_uint curr_sql_stmt_cursor = 0;
    Description next_sql_stmt_str;
	t_uint next_sql_stmt_cursor = 0;

    if (p_stream_ptr->good ())
    {
		while (1)
		{
			//  Look for  ';'  character which denotes the end of
			//    an SQL statement.
			//
			while (curr_sql_stmt_str.char_at (curr_sql_stmt_cursor) != ';')
			{
				if (! increment_cursor (curr_sql_stmt_str, curr_sql_stmt_cursor, p_stream_ptr, FALSE))
				{
					goto end_of_sql_file;
				}
				
				if (curr_sql_stmt_str.char_at(curr_sql_stmt_cursor) == '\'')
				{
					//  This begins a tick delimited string - find end of
					//    tick delimited string.
					//
					do
					{
						if (! increment_cursor
							(curr_sql_stmt_str, curr_sql_stmt_cursor, p_stream_ptr, TRUE))
						{
							goto end_of_sql_file;
						}

						t_boolean handling_potential_repeated_ticks = TRUE;
						while (handling_potential_repeated_ticks)
						{
							if (curr_sql_stmt_str.char_at (curr_sql_stmt_cursor) == '\'')
							{
								//  Have found a tick - make sure it is not a
								//    repeated tick...
								//
								if ((curr_sql_stmt_cursor + 1)
									< curr_sql_stmt_str.length ())
								{
									if (curr_sql_stmt_str.char_at(curr_sql_stmt_cursor + 1)
										== '\'')
									{
										//  Have found repeated tick - increment
										//    beyond both ticks.
										//
										if (! increment_cursor
											(curr_sql_stmt_str, curr_sql_stmt_cursor, p_stream_ptr, TRUE))
										{
											goto end_of_sql_file;
										}
										if (! increment_cursor
											(curr_sql_stmt_str, curr_sql_stmt_cursor, p_stream_ptr, TRUE))
										{
											goto end_of_sql_file;
										}
									}
									else
									{
										handling_potential_repeated_ticks
											= FALSE;
									}
								}
								else
								{
									//  Next character on line does not exist
									//    - means that this is the end of the
									//    line...
									//
									handling_potential_repeated_ticks = FALSE;
								}
							}
							else
							{
								handling_potential_repeated_ticks = FALSE;
							}
						}
					}
					while (curr_sql_stmt_str.char_at(curr_sql_stmt_cursor) != '\'');
					
					//  Have found the end of the tick delimited string -
					//    increment beyond this tick.
					//
					if (! increment_cursor
						(curr_sql_stmt_str, curr_sql_stmt_cursor, p_stream_ptr, FALSE))
					{
						goto end_of_sql_file;
					}
				}
			}
			
			
			if ((curr_sql_stmt_cursor + 1) < curr_sql_stmt_str.length ())
			{
				curr_sql_stmt_cursor++;
				t_uint cursor_position = curr_sql_stmt_cursor ;
				
				//  Need to 'prime' the next_sql_stmt_str with some white space
				//    so that the increment cursor function works properly.
				//
				next_sql_stmt_str = "  ";
                Description temp_stmt_str( curr_sql_stmt_str.length() );
                curr_sql_stmt_str.parse_to_end (curr_sql_stmt_cursor, temp_stmt_str);
				next_sql_stmt_str += temp_stmt_str;
				curr_sql_stmt_str.truncate (cursor_position);
			}
			curr_sql_stmt_cursor = 0;
			
			//  Execute the SQL Statement.
			//
			if (! import_sql_statement (curr_sql_stmt_str))
			{
				GS_ui::inform (UI_INFORM__ERROR, GS_string (
					"Aborting commitment of ALL SQL statements."));
			}
			
			curr_sql_stmt_str = next_sql_stmt_str;
			next_sql_stmt_str.reset (0);
		}
    }


end_of_sql_file:
    curr_sql_stmt_str.consume_white_space (curr_sql_stmt_cursor);
    if (curr_sql_stmt_cursor < curr_sql_stmt_str.length ())
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string (
	    "Partial SQL statement left at bottom of file."));
	GS_ui::inform (UI_INFORM__ERROR, GS_string (
	    "Aborting commitment of ALL SQL statements."));
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"End  GS_import::import_sql_file (TRUE)."));
    return TRUE;
}





t_boolean
GS_import::import_sql_statement (const Description& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_import::import_sql_statement (p_stmt_str=\"%s\").",
	p_stmt_str.char_ptr ()));


    extern int GS_domain_code;

    //  If this is the first statement processed, then reset all related flags
    //    so that all instance relationships will be re-calculated.
    //
    static is_first_stmt_to_cause_rerelate = TRUE;


    Description stmt_str (p_stmt_str);
    t_uint stmt_cursor = 0;

    //  Remove the ';' off end of statement if one exists.
    //
    for (t_uint i = stmt_str.length () - 1;
		((i >= 0) && (vcharIsWhiteSpace (stmt_str.char_at(i))));
		i--);
		if (stmt_str.char_at(i) == ';')
		{
			stmt_str.truncate(i);
		}

	GS_UI_INFORM_START(UI_INFORM__STMT)
    Description info_msg ("Interpreting --> ");
	info_msg += stmt_str;
	info_msg += " <-- Statement.";
	GS_UI_INFORM_END(UI_INFORM__STMT, info_msg);

    Description operation_str;
    stmt_str.parse_token (stmt_cursor, operation_str);
    operation_str.convert_to_upper_case ();
    if (operation_str == create_string)
    {
	Description create_type_str;
    stmt_str.parse_token (stmt_cursor, create_type_str);
	create_type_str.convert_to_upper_case ();
	if (create_type_str == table_string)
	{
	    Description obj_name_str;
        stmt_str.parse_token (stmt_cursor, obj_name_str);
	    obj_name_str.convert_to_upper_case ();
	    mc_dbms_Set <I_Object*>* obj_coll_ptr
		= I_Object::find_Object_by_key_letter
		    (GS_gen_sim_db_ptr, obj_name_str.char_ptr ());

	    if (! obj_coll_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "GS_import::import_sql_statement ():  Creation of I_Object collection in find returned 0."));
		return FALSE;
	    }

	    if (obj_coll_ptr->cardinality () < 1)
	    {
		//  Get rid of the collection of objects from the find &
		//    build the new object into the schema.
		//
		delete obj_coll_ptr;
		I_Object* obj_ptr = I_Object::create
		    (GS_gen_sim_db_ptr, obj_name_str.char_ptr ());
		if (! obj_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Unable to  create an instance of 'I_Object'."));
		    return FALSE;
		}
		
        Description dummy;
		stmt_str.parse_token ('(', stmt_cursor, dummy);
		if (stmt_str.char_at (stmt_cursor) != '(')
		{
		    print_create_table_usage ();
		    return FALSE;
		}
		stmt_cursor++;
		t_uint attr_with_type_set_cursor = 0;
		Description attr_with_type_set_str;
		stmt_str.parse_token (')', stmt_cursor, attr_with_type_set_str, TRUE);
		if (stmt_str.char_at (stmt_cursor) != ')')
		{
		    print_create_table_usage ();
		    return FALSE;
		}
		stmt_cursor++;

		for (unsigned int num_attrs = 0;
		    attr_with_type_set_cursor < attr_with_type_set_str.length ();
		    num_attrs++)
		{
			t_uint attr_with_type_cursor = 0;
			Description attr_with_type_str;
			attr_with_type_set_str.parse_token (',', attr_with_type_set_cursor, attr_with_type_str);
			if (attr_with_type_set_str.char_at (attr_with_type_set_cursor) == ',')
			{
				attr_with_type_set_cursor++;
			}
			
			if (attr_with_type_str.length() != 0)
			{
				Description attr_name_str;
				attr_with_type_str.parse_token (attr_with_type_cursor, attr_name_str);
				attr_name_str.convert_to_upper_case ();
				Description attr_type_str;
				attr_with_type_str.parse_token (attr_with_type_cursor, attr_type_str);
				attr_type_str.convert_to_upper_case ();
				
				if (attr_type_str == boolean_string)
				{
					I_Attribute* attr_ptr
						= I_Attribute::create (GS_gen_sim_db_ptr,
						attr_name_str.char_ptr (), BOOLEAN_DATATYPE);
					if (! attr_ptr)
					{
						LOG_ERROR ((L_log_string,
							"GS_import::import_sql_statement ():  Unable to  crate an instance of 'I_Attribute'."));
						return FALSE;
					}
					attr_ptr->relate_R102 (obj_ptr);
				}
				else if (attr_type_str == integer_string)
				{
					I_Attribute* attr_ptr
						= I_Attribute::create (GS_gen_sim_db_ptr,
						attr_name_str.char_ptr (), INTEGER_DATATYPE);
					if (! attr_ptr)
					{
						LOG_ERROR ((L_log_string,
							"GS_import::import_sql_statement ():  Unable to  crate an instance of 'I_Attribute'."));
						return FALSE;
					}
					attr_ptr->relate_R102 (obj_ptr);
				}
				else if (attr_type_str == real_string)
				{
					I_Attribute* attr_ptr
						= I_Attribute::create (GS_gen_sim_db_ptr,
						attr_name_str.char_ptr (), REAL_DATATYPE);
					if (! attr_ptr)
					{
						LOG_ERROR ((L_log_string,
							"GS_import::import_sql_statement ():  Unable to  crate an instance of 'I_Attribute'."));
						return FALSE;
					}
					attr_ptr->relate_R102 (obj_ptr);
				}
				else if (attr_type_str == string_string)
				{
					I_Attribute* attr_ptr
						= I_Attribute::create (GS_gen_sim_db_ptr,
						attr_name_str.char_ptr (), STRING_DATATYPE);
					if (! attr_ptr)
					{
						LOG_ERROR ((L_log_string,
							"GS_import::import_sql_statement ():  Unable to  crate an instance of 'I_Attribute'."));
						return FALSE;
					}
					attr_ptr->relate_R102 (obj_ptr);
				}
				else if (attr_type_str == unique_id_string)
				{
					I_Attribute* attr_ptr
						= I_Attribute::create (GS_gen_sim_db_ptr,
						attr_name_str.char_ptr (), UNIQUE_ID_DATATYPE);
					if (! attr_ptr)
					{
						LOG_ERROR ((L_log_string,
							"GS_import::import_sql_statement ():  Unable to  crate an instance of 'I_Attribute'."));
						return FALSE;
					}
					attr_ptr->relate_R102 (obj_ptr);
				}
				else
				{
					print_create_table_usage ();
					return FALSE;
				}
			}
			}
	    }
	    else
	    {
		//  Migrate from current view of schema to new view of schema.
		//
		if (obj_coll_ptr->cardinality () > 1)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of I_Object Collection in resulted in more than one instance! - continuing with one of the instance."));
		}

		I_Object* obj_ptr = obj_coll_ptr->pick ();
		delete obj_coll_ptr;

		GS_ui::inform (UI_INFORM__ERROR, GS_string("Object already exists - migration is not supported at this time."));
	    }
	}
	else if (create_type_str == rop_string)
	{
	    Description rop_type_str;
        stmt_str.parse_token (stmt_cursor, rop_type_str);
	    rop_type_str.convert_to_upper_case ();
	    if (rop_type_str == ref_id_string)
	    {
			Description rel_number_str;
            stmt_str.parse_token (stmt_cursor, rel_number_str);
			rel_number_str.convert_to_upper_case ();
		
			Description from_str;
            stmt_str.parse_token (stmt_cursor, from_str);
			from_str.convert_to_upper_case ();
			if (from_str != from_string)
			{
			    print_create_rop_ref_id_usage ();
				return FALSE;
			}

			Description from_mult_cond_str;
            stmt_str.parse_token (stmt_cursor, from_mult_cond_str);
			from_mult_cond_str.convert_to_upper_case ();
			if ((from_mult_cond_str != num_one_string)
			    && (from_mult_cond_str != onec_string)
			    && (from_mult_cond_str != m_string)
			    && (from_mult_cond_str != mc_string))
			{
			    print_create_rop_ref_id_usage ();
				return FALSE;
			}

			Description REF_side_obj_name_str;
            stmt_str.parse_token (stmt_cursor, REF_side_obj_name_str);
			REF_side_obj_name_str.convert_to_upper_case ();
			mc_dbms_Set <I_Object*>* REF_side_obj_coll_ptr
				= I_Object::find_Object_by_key_letter
				(GS_gen_sim_db_ptr, REF_side_obj_name_str.char_ptr ());

		if (! REF_side_obj_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of REF side I_Object collection in find returned 0."));
		    return FALSE;
		}

		if (REF_side_obj_coll_ptr->cardinality () < 1)
		{
		    Description err_msg ("Reference Side Object '");
			err_msg += REF_side_obj_name_str;
			err_msg += "' Unknown.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    delete REF_side_obj_coll_ptr;
		    return FALSE;
		}

		if (REF_side_obj_coll_ptr->cardinality () > 1)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Reference side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
		}

		I_Object* REF_side_obj_ptr = REF_side_obj_coll_ptr->pick ();
		delete REF_side_obj_coll_ptr;
		if (! REF_side_obj_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"I_Object '%s' found but has a 0 pointer.",
			REF_side_obj_name_str.char_ptr ()));
		    return FALSE;
		}

		I_Attribute* REF_side_attr_ptr [GS_MAX_NUM_ATTRS_PER_REF];
        Description dummy;
		stmt_str.parse_token ('(', stmt_cursor, dummy);
		if (stmt_str.char_at (stmt_cursor) != '(')
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		stmt_cursor++;
		t_uint REF_side_attr_set_cursor = 0;
		Description REF_side_attr_set_str;
        stmt_str.parse_token (')', stmt_cursor, REF_side_attr_set_str);
		if (stmt_str.char_at (stmt_cursor) != ')')
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		stmt_cursor++;

		for (unsigned int num_refs = 0;
		    REF_side_attr_set_cursor < REF_side_attr_set_str.length ();
		    num_refs++)
		{
		    Description REF_side_attr_str;
			REF_side_attr_set_str.parse_token (',', REF_side_attr_set_cursor, REF_side_attr_str);
		    REF_side_attr_str.convert_to_upper_case ();
		    if (REF_side_attr_set_str.char_at (REF_side_attr_set_cursor) == ',')
		    {
				REF_side_attr_set_cursor++;
		    }

		    if (REF_side_attr_str.length() != 0)
		    {
			mc_dbms_Set <I_Attribute*>* REF_side_attr_coll_ptr
			    = REF_side_obj_ptr->find_Attribute_R102_by_name
				(REF_side_attr_str.char_ptr ());

			if (! REF_side_attr_coll_ptr)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  Creation of REF side I_Attribute collection in find returned 0."));
			    return FALSE;
			}

			if (REF_side_attr_coll_ptr->cardinality () < 1)
			{
				Description err_msg ("Reference Side Attribute '");
				err_msg += REF_side_attr_str;
				err_msg += "' Unknown.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			    print_create_rop_ref_id_usage ();
			    delete REF_side_attr_coll_ptr;
			    return FALSE;
			}

			if (REF_side_attr_coll_ptr->cardinality () > 1)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  Reference side I_Attribute Collection resulted in more than one instance! - continuing with one of the instances."));
			}

			REF_side_attr_ptr [num_refs]
			    = REF_side_attr_coll_ptr->pick ();
			delete REF_side_attr_coll_ptr;

			if (! REF_side_attr_ptr [num_refs])
			{
			    LOG_ERROR ((L_log_string,
				"I_Attribute '%s.%s' in collection has 0 ptr.",
				REF_side_obj_name_str.char_ptr(), REF_side_attr_str.char_ptr()));
			    return FALSE;
			}
		    }
		}
		
		Description from_rel_phrase_str;
		Description to_str;
        stmt_str.parse_token (stmt_cursor, to_str);
		to_str.convert_to_upper_case ();
		if (to_str != to_string)
		{
		    if (to_str == phrase_string)
		    {
			stmt_str.parse_token__ticked_str (stmt_cursor, from_rel_phrase_str);
			stmt_str.parse_token (stmt_cursor, to_str);
			to_str.convert_to_upper_case ();
			if (to_str != to_string)
			{
			    print_create_rop_ref_id_usage ();
			    return FALSE;
			}
		    }
		    else
		    {
			print_create_rop_ref_id_usage ();
			return FALSE;
		    }
		}

		Description to_mult_cond_str;
        stmt_str.parse_token (stmt_cursor, to_mult_cond_str);
		to_mult_cond_str.convert_to_upper_case ();
		if ((to_mult_cond_str != num_one_string)
		    && (to_mult_cond_str != onec_string)
		    && (to_mult_cond_str != m_string)
		    && (to_mult_cond_str != mc_string))
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		
		Description ID_side_obj_name_str;
        stmt_str.parse_token (stmt_cursor, ID_side_obj_name_str);
		ID_side_obj_name_str.convert_to_upper_case ();
		mc_dbms_Set <I_Object*>* ID_side_obj_coll_ptr
		    = I_Object::find_Object_by_key_letter
			(GS_gen_sim_db_ptr, ID_side_obj_name_str.char_ptr ());

		if (! ID_side_obj_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of ID side I_Object collection in find returned 0."));
		    return FALSE;
		}

		if (ID_side_obj_coll_ptr->cardinality () < 1)
		{
		    Description err_msg ("Identifier Side Object '");
			err_msg += ID_side_obj_name_str;
			err_msg += "' Unknown.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    delete ID_side_obj_coll_ptr;
		    return FALSE;
		}

		if (ID_side_obj_coll_ptr->cardinality () > 1)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Identifier side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
		}

		I_Object* ID_side_obj_ptr = ID_side_obj_coll_ptr->pick ();
		delete ID_side_obj_coll_ptr;

		if (! ID_side_obj_ptr)
		{
		    Description err_msg ("Object '");
			err_msg += ID_side_obj_name_str;
			err_msg += "' NOT found.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		
		I_Attribute* ID_side_attr_ptr [GS_MAX_NUM_ATTRS_PER_REF];
		stmt_str.parse_token ('(', stmt_cursor, dummy);
		if (stmt_str.char_at (stmt_cursor) != '(')
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		stmt_cursor++;
		t_uint ID_side_attr_set_cursor = 0;
		Description ID_side_attr_set_str;
        stmt_str.parse_token (')', stmt_cursor, ID_side_attr_set_str);
		if (stmt_str.char_at (stmt_cursor) != ')')
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		stmt_cursor++;

		for (unsigned int num_ids = 0;
		    ID_side_attr_set_cursor < ID_side_attr_set_str.length ();
		    num_ids++)
		{
		    Description ID_side_attr_str;
			ID_side_attr_set_str.parse_token (',', ID_side_attr_set_cursor, ID_side_attr_str);
		    ID_side_attr_str.convert_to_upper_case ();
		    if (ID_side_attr_set_str.char_at (ID_side_attr_set_cursor) == ',')
		    {
			ID_side_attr_set_cursor++;
		    }

		    if (ID_side_attr_str.length() != 0)
		    {
			mc_dbms_Set <I_Attribute*>* ID_side_attr_coll_ptr
			    = ID_side_obj_ptr->find_Attribute_R102_by_name (ID_side_attr_str.char_ptr ());

			if (! ID_side_attr_coll_ptr)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  Creation of ID side I_Attribute collection in find returned 0."));
			    return FALSE;
			}

			if (ID_side_attr_coll_ptr->cardinality () < 1)
			{
				Description err_msg ("Identifier Side Attribute '");
				err_msg += ID_side_attr_str;
				err_msg += " Unknown.";
			    GS_ui::inform (UI_INFORM__ERROR, err_msg);
			    print_create_rop_ref_id_usage ();
			    delete ID_side_attr_coll_ptr;
			    return FALSE;
			}

			if (ID_side_attr_coll_ptr->cardinality () > 1)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  Identifier side I_Attribute Collection resulted in more than one instance! - continuing with one of the instances."));
			}

			ID_side_attr_ptr [num_ids]
			    = ID_side_attr_coll_ptr->pick ();
			delete ID_side_attr_coll_ptr;

			if (! ID_side_attr_ptr [num_ids])
			{
			    LOG_ERROR ((L_log_string,
				"I_Attribute '%s.%s' in collection has 0 ptr.",
				ID_side_obj_name_str.char_ptr(), ID_side_attr_str.char_ptr()));
			    return FALSE;
			}
		    }
		}

		Description to_rel_phrase_str;
		Description phrase_keyword_str;
        stmt_str.parse_token (stmt_cursor, phrase_keyword_str);
		phrase_keyword_str.convert_to_upper_case ();
		if (phrase_keyword_str == phrase_string)
		{
		    stmt_str.parse_token__ticked_str (stmt_cursor, to_rel_phrase_str);
		}

		
		if (num_refs != num_ids)
		{
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("The number of referential attributes does not match the number of identifier attributes."));
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
	    
		//  Find the instance of 'I_Relationship' - if it does not exist
		//    yet, then create it.
		//
		mc_dbms_Set <I_Relationship*>* rel_coll_ptr
		    = I_Relationship::find_Relationship_by_number
			(GS_gen_sim_db_ptr, rel_number_str.char_ptr ());

		if (! rel_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of I_Relationship collection in find returned 0."));
		    return FALSE;
		}

		I_Relationship* rel_ptr = 0;
		if (rel_coll_ptr->cardinality () >= 1)
		{
		    if (rel_coll_ptr->cardinality () > 1)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  I_Relationship Collection resulted in more than one instance! - continuing with one of the instances."));
		    }
		    rel_ptr = rel_coll_ptr->pick ();
		}

		delete rel_coll_ptr;

		if (! rel_ptr)
		{
		    rel_ptr = I_Relationship::create
			(GS_gen_sim_db_ptr, rel_number_str.char_ptr ());
		    if (! rel_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  Unable to create an instance of 'I_Relationship'."));
			return FALSE;
		    }
		}
		
		
		//  Create an instance of 'I_ID_REF_Rel_Obj_Pair' and relate it
		//    to the instance of 'I_Relationship' & instances of
		//    'I_Object'.
		//
		I_ID_REF_Rel_Obj_Pair* ir_rop_ptr
		    = I_ID_REF_Rel_Obj_Pair::create (GS_gen_sim_db_ptr);
		if (! ir_rop_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Unable to create an instance of 'I_ID_REF_Rel_Obj_Pair'."));
		    return FALSE;
		}
		ir_rop_ptr->relate_R2003 (rel_ptr);
		ir_rop_ptr->relate_R2005 (ID_side_obj_ptr);
		ir_rop_ptr->relate_R2006 (REF_side_obj_ptr);

		if ((from_mult_cond_str ==onec_string) || (from_mult_cond_str == mc_string))
		{
		    ir_rop_ptr->set_OTH_side_is_conditional (TRUE);
		}
		if ((from_mult_cond_str == m_string) || (from_mult_cond_str == mc_string))
		{
		    ir_rop_ptr->set_OTH_side_is_many (TRUE);
		}
		if ((to_mult_cond_str == onec_string) || (to_mult_cond_str == mc_string))
		{
		    ir_rop_ptr->set_ONE_side_is_conditional (TRUE);
		}
		if ((to_mult_cond_str == m_string ) || (to_mult_cond_str == mc_string))
		{
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("Specification of 'M' or 'Mc' on ID sid (i.e., the TO side)\nof ROP REF_ID does not make sense - can not be store referential\nattribute values which refer to more than one ID value..."));
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		ir_rop_ptr->set_OTH_side_phrase
		    (from_rel_phrase_str.char_ptr ());
		ir_rop_ptr->set_ONE_side_phrase
		    (to_rel_phrase_str.char_ptr ());
		
		//  Create instances of 'I_ID_Attribute_Reference' and relate
		//    them to just created instance 'I_Related_Object_Pair' &
		//    instances of 'I_Attribute'.
		//
		for (unsigned int i = 0;
		    i < num_refs;
		    i++)
		{
		    I_ID_Attribute_Reference* id_attr_ref_ptr
			= I_ID_Attribute_Reference::create (GS_gen_sim_db_ptr);
		    if (! id_attr_ref_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  Unable to create an instance of 'I_ID_Attribute_Reference'."));
			return FALSE;
		    }
		    id_attr_ref_ptr->relate_R2007 (ir_rop_ptr);
		    id_attr_ref_ptr->relate_R2008 (ID_side_attr_ptr [i]);
		    id_attr_ref_ptr->relate_R2009 (REF_side_attr_ptr [i]);
		}
	    }
	    else if (rop_type_str == chain_string)
	    {
		Description rel_number_str;
        stmt_str.parse_token (stmt_cursor, rel_number_str);
		rel_number_str.convert_to_upper_case ();
		
		Description from_str;
        stmt_str.parse_token (stmt_cursor, from_str);
		from_str.convert_to_upper_case ();
		if (from_str != from_string)
		{
		    print_create_rop_chain_usage ();
		    return FALSE;
		}

		Description from_mult_cond_str;
        stmt_str.parse_token (stmt_cursor, from_mult_cond_str);
		from_mult_cond_str.convert_to_upper_case ();
		if ((from_mult_cond_str != num_one_string)
		    && (from_mult_cond_str != onec_string)
		    && (from_mult_cond_str != m_string)
		    && (from_mult_cond_str != mc_string))
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}

		Description from_obj_name_str;
        stmt_str.parse_token (stmt_cursor, from_obj_name_str);
		from_obj_name_str.convert_to_upper_case ();
		mc_dbms_Set <I_Object*>* from_obj_coll_ptr
		    = I_Object::find_Object_by_key_letter
			(GS_gen_sim_db_ptr, from_obj_name_str.char_ptr ());

		if (! from_obj_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of FROM side I_Object collection in find returned 0."));
		    return FALSE;
		}

		if (from_obj_coll_ptr->cardinality () < 1)
		{
		    Description err_msg ("FROM Side Object '");
			err_msg += from_obj_name_str;
			err_msg += "' Unknown.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    delete from_obj_coll_ptr;
		    return FALSE;
		}

		if (from_obj_coll_ptr->cardinality () > 1)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  FROM side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
		}

		I_Object* from_obj_ptr = from_obj_coll_ptr->pick ();
		delete from_obj_coll_ptr;
		if (! from_obj_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"I_Object '%s' found but has a 0 pointer.",
			from_obj_name_str.char_ptr ()));
		    return FALSE;
		}
		
		Description from_rel_phrase_str;
		Description to_str;
        stmt_str.parse_token (stmt_cursor, to_str);
		to_str.convert_to_upper_case ();
		if (to_str != to_string)
		{
		    if (to_str == phrase_string)
		    {
			stmt_str.parse_token__ticked_str (stmt_cursor, from_rel_phrase_str);
			stmt_str.parse_token (stmt_cursor, to_str);
			to_str.convert_to_upper_case ();
			if (to_str != to_string)
			{
			    print_create_rop_ref_id_usage ();
			    return FALSE;
			}
		    }
		    else
		    {
			print_create_rop_ref_id_usage ();
			return FALSE;
		    }
		}

		Description to_mult_cond_str;
        stmt_str.parse_token (stmt_cursor, to_mult_cond_str);
		to_mult_cond_str.convert_to_upper_case ();
		if ((to_mult_cond_str != num_one_string)
		    && (to_mult_cond_str != onec_string)
		    && (to_mult_cond_str != m_string)
		    && (to_mult_cond_str != mc_string))
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		
		Description to_obj_name_str;
        stmt_str.parse_token (stmt_cursor, to_obj_name_str);
		to_obj_name_str.convert_to_upper_case ();
		mc_dbms_Set <I_Object*>* to_obj_coll_ptr
		    = I_Object::find_Object_by_key_letter (GS_gen_sim_db_ptr,
			to_obj_name_str.char_ptr ());

		if (! to_obj_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of TO side I_Object collection in find returned 0."));
		    return FALSE;
		}

		if (to_obj_coll_ptr->cardinality () < 1)
		{
		    Description err_msg ("TO Side Object '");
			err_msg += to_obj_name_str;
			err_msg += "' Unknown.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    delete to_obj_coll_ptr;
		    return FALSE;
		}

		if (to_obj_coll_ptr->cardinality () > 1)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  TO side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
		}

		I_Object* to_obj_ptr = to_obj_coll_ptr->pick ();
		delete to_obj_coll_ptr;

		if (! to_obj_ptr)
		{
		    Description err_msg ("Object '");
			err_msg += to_obj_name_str;
			err_msg += "' NOT found.";
		    GS_ui::inform (UI_INFORM__ERROR, err_msg);
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}
		
		Description through_str;
        stmt_str.parse_token (stmt_cursor, through_str);
		through_str.convert_to_upper_case ();
		if (through_str != through_string)
		{
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}

		t_uint chain_cursor = 0;
		Description chain_str;
        stmt_str.parse_token ("PHRASE", stmt_cursor, chain_str);
		Description start_obj_name_str;
        chain_str.parse_token("->", chain_cursor, start_obj_name_str);
		if (start_obj_name_str != from_obj_name_str)
		{
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("Object starting the chain does not match the FROM side object."));
		    print_create_rop_ref_id_usage ();
		    return FALSE;
		}

		Description ONE_side_chain_equiv_str;

		I_Object* int_obj_ptr [32];
		int_obj_ptr [0] = from_obj_ptr;
		I_Relationship* int_rel_ptr [32];
		int_rel_ptr [0] = 0;
		I_Related_Object_Pair* int_rop_ptr [32];
		int_rop_ptr [0] = 0;
		for (unsigned int curr_link_num = 1;
		    ((chain_cursor < chain_str.length ()) &&
			(curr_link_num < 32));
		    curr_link_num++)
		{
		    if ((chain_str.char_at(chain_cursor) != '-') ||
		       (chain_str.char_at(chain_cursor + 1) != '>'))
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string("Expected '->' in Chain"));
			print_create_rop_ref_id_usage ();
			return FALSE;
		    }
		    chain_cursor++;
		    chain_cursor++;
			
		    if (curr_link_num == 1)
		    {
			t_uint chain_str_cursor = chain_cursor;
			chain_str.parse_to_end (chain_cursor, ONE_side_chain_equiv_str);
			chain_cursor = chain_str_cursor;
		    }

		    Description int_obj_name_str;
            chain_str.parse_token ('[', chain_cursor, int_obj_name_str);
		    chain_cursor++;

		    mc_dbms_Set <I_Object*>* int_obj_coll_ptr
			= I_Object::find_Object_by_key_letter
			    (GS_gen_sim_db_ptr, int_obj_name_str.char_ptr ());

		    if (! int_obj_coll_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  Creation of INT I_Object collection in find returned 0."));
			return FALSE;
		    }

		    if (int_obj_coll_ptr->cardinality () < 1)
		    {
			Description err_msg ("Object '");
			err_msg += int_obj_name_str;
			err_msg += "' Unknown.";
			GS_ui::inform (UI_INFORM__ERROR, err_msg);
			print_create_rop_ref_id_usage ();
			delete int_obj_coll_ptr;
			return FALSE;
		    }

		    if (int_obj_coll_ptr->cardinality () > 1)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  INT I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
		    }

		    int_obj_ptr [curr_link_num] = int_obj_coll_ptr->pick ();
		    delete int_obj_coll_ptr;
		    if (! int_obj_ptr [curr_link_num])
		    {
			LOG_ERROR ((L_log_string,
			   "I_Object '%s' found but has a 0 pointer.",
			   int_obj_name_str.char_ptr ()));
			return FALSE;
		    }
		    
		    Description int_rel_number_str;
		    Description direction_str;
			t_uint full_rel_number_cursor = 0;
		    Description full_rel_number_str;
			chain_str.parse_token (']', chain_cursor, full_rel_number_str); 
		    if (chain_str.char_at (chain_cursor) != ']')
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string("Expected ']' in Chain."));
			print_create_rop_chain_usage ();
			return FALSE;
		    } 
		    chain_cursor++;

		    full_rel_number_str.parse_token ('.', full_rel_number_cursor, int_rel_number_str);
		    if (full_rel_number_str.char_at (full_rel_number_cursor) == '.')
		    {
			//  Direction string follows.
			//
			full_rel_number_cursor++;
			full_rel_number_str.parse_to_end (full_rel_number_cursor, direction_str);
		    }
		
		    mc_dbms_Set <I_Relationship*>* rel_coll_ptr
			= I_Relationship::find_Relationship_by_number
			    (GS_gen_sim_db_ptr, int_rel_number_str.char_ptr ());

		    if (! rel_coll_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  Creation of I_Relationship collection in find returned 0."));
			return FALSE;
		    }

		    if (rel_coll_ptr->cardinality () >= 1)
		    {
			if (rel_coll_ptr->cardinality () > 1)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  I_Relationship Collection resulted in more than one instance! - continuing with one of the instances."));
			}
			int_rel_ptr [curr_link_num] = rel_coll_ptr->pick ();
		    }

		    delete rel_coll_ptr;

		    if (! int_rel_ptr [curr_link_num])
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  I_Relationship '%s' NOT found.",
			    int_rel_number_str.char_ptr ()));
			return FALSE;
		    }
    
		    int_rop_ptr [curr_link_num] = 0;
		    if ((direction_str.length() == 0) || (direction_str == ir_string))
		    {
			mc_dbms_List <I_Related_Object_Pair*>* id_rop_coll_ptr
			    = int_obj_ptr [curr_link_num - 1]->
				get_Related_Object_Pair_R2005_coll_ptr ();
			if (! id_rop_coll_ptr)
			{
			    LOG_ERROR ((L_log_string,
				"GS_import::import_sql_statement ():  R2005 coll ptr to I_ROP from O_OBJ is 0."));
			    return FALSE;
			}
			I_Related_Object_Pair* id_rop_ptr = 0;
			FOR_ALL_ELEMENTS
			    (id_rop_ptr,
			    I_Related_Object_Pair,
			    id_rop_coll_ptr,
			    id_rop_cursor)
			{
			    if ((id_rop_ptr->get_Object_R2006_ptr ()
				    == int_obj_ptr [curr_link_num])
				&&
				(id_rop_ptr->get_Relationship_R2003_ptr ()
				    == int_rel_ptr [curr_link_num]))
			    {
				if (int_rop_ptr [curr_link_num])
				{
				    LOG_ERROR ((L_log_string, "GS_import::import_sql_statement ():  More than 1 instance of I_ROP found matching chain."));
				    return FALSE;
				}
				else
				{
				    int_rop_ptr [curr_link_num] = id_rop_ptr;
				}
			    }
			}
		    }

		    if ((! int_rop_ptr [curr_link_num])
			&&
		      ((direction_str.length() == 0) || (direction_str == ri_string)))
		    {
			mc_dbms_List <I_Related_Object_Pair*>* ref_rop_coll_ptr
			    = int_obj_ptr [curr_link_num - 1]->
			    get_Related_Object_Pair_R2006_coll_ptr ();
			if (! ref_rop_coll_ptr)
			{
			    LOG_ERROR ((L_log_string, "I_relate::relate_object_instance ():  R2006 coll ptr to I_ROP from O_OBJ is 0."));
			    return FALSE;
			}
			I_Related_Object_Pair* ref_rop_ptr = 0;
			FOR_ALL_ELEMENTS
			    (ref_rop_ptr,
			    I_Related_Object_Pair,
			    ref_rop_coll_ptr,
			    ref_rop_cursor)
			{
			    if ((ref_rop_ptr->get_Object_R2005_ptr ()
				    == int_obj_ptr [curr_link_num])
				&&
				(ref_rop_ptr->get_Relationship_R2003_ptr ()
				    == int_rel_ptr [curr_link_num]))
			    {
				if (int_rop_ptr [curr_link_num])
				{
				    LOG_ERROR ((L_log_string, "GS_import::import_sql_statement ():  More than 1 instance of I_ROP found matching chain."));
				    return FALSE;
				}
				else
				{
				    int_rop_ptr [curr_link_num] = ref_rop_ptr;
				}
			    }
			}
		    }

		    if (! int_rop_ptr [curr_link_num])
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string("Unable to find instance of ROP matching chain link."));
			return FALSE;
		    }

		    chain_str.consume_white_space (chain_cursor);
		}

		if (to_obj_name_str != int_obj_ptr [curr_link_num - 1]->
		    get_key_letter ().char_ptr ())
		{
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("Object ending the chain does not match the TO side object."));
		    return FALSE;
		}

		Description to_rel_phrase_str;
		Description phrase_keyword_str;
        stmt_str.parse_token (stmt_cursor, phrase_keyword_str);
		phrase_keyword_str.convert_to_upper_case ();
		if (phrase_keyword_str == phrase_string)
		{
		    stmt_str.parse_token__ticked_str (stmt_cursor, to_rel_phrase_str);
		}

	    
		//  Find the instance of 'I_Relationship' - if it does not exist
		//    yet, then create it.
		//
		mc_dbms_Set <I_Relationship*>* rel_coll_ptr
		    = I_Relationship::find_Relationship_by_number
			(GS_gen_sim_db_ptr, rel_number_str.char_ptr ());

		if (! rel_coll_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Creation of I_Relationship collection in find returned 0."));
		    return FALSE;
		}

		I_Relationship* rel_ptr = 0;
		if (rel_coll_ptr->cardinality () >= 1)
		{
		    if (rel_coll_ptr->cardinality () > 1)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  I_Relationship Collection resulted in more than one instance! - continuing with one of the instances."));
		    }
		    rel_ptr = rel_coll_ptr->pick ();
		}

		delete rel_coll_ptr;

		if (! rel_ptr)
		{
		    rel_ptr = I_Relationship::create
			(GS_gen_sim_db_ptr, rel_number_str.char_ptr ());
		    if (! rel_ptr)
		    {
			LOG_ERROR ((L_log_string,
			    "GS_import::import_sql_statement ():  Unable to create an instance of 'I_Relationship'."));
			return FALSE;
		    }
		}
		

		//  Create an instance of 'I_Chain_Rel_Obj_Pair' and relate it
		//    to the instance of 'I_Relationship' & instances of
		//    'I_Object'.
		//
		I_Chain_Rel_Obj_Pair* c_rop_ptr
		    = I_Chain_Rel_Obj_Pair::create (GS_gen_sim_db_ptr);
		if (! c_rop_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  Unable to create an instance of 'I_Chain_Rel_Obj_Pair'."));
		    return FALSE;
		}
		c_rop_ptr->relate_R2003 (rel_ptr);
		c_rop_ptr->relate_R2005 (to_obj_ptr);
		c_rop_ptr->relate_R2006 (from_obj_ptr);
		c_rop_ptr->set_ONE_side_chain_equiv
		    (ONE_side_chain_equiv_str.char_ptr ());

		if ((from_mult_cond_str == onec_string) || (from_mult_cond_str == mc_string))
		{
		    c_rop_ptr->set_OTH_side_is_conditional (TRUE);
		}
		if ((from_mult_cond_str == m_string) || (from_mult_cond_str == mc_string))
		{
		    c_rop_ptr->set_OTH_side_is_many (TRUE);
		}
		if ((to_mult_cond_str == onec_string) || (to_mult_cond_str == mc_string))
		{
		    c_rop_ptr->set_ONE_side_is_conditional (TRUE);
		}
		if ((to_mult_cond_str == m_string ) || (to_mult_cond_str == mc_string))
		{
		    c_rop_ptr->set_ONE_side_is_many (TRUE);
		}
		c_rop_ptr->set_OTH_side_phrase
		    (from_rel_phrase_str.char_ptr ());
		c_rop_ptr->set_ONE_side_phrase
		    (to_rel_phrase_str.char_ptr ());
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR, GS_string("Do not recognize CREATE ROP type."));
		print_create_rop_ref_id_usage ();
		print_create_rop_chain_usage ();
	    }


	    //  If this is the first statement processed, then reset all related
	    //    flags so that all instance relationships will be re-calculated
	    //
	    if (is_first_stmt_to_cause_rerelate)
	    {
		mc_dbms_List<I_Object_Instance*>* oinst_coll_ptr =
		    I_Object_Instance::get_class_extent_ptr (GS_gen_sim_db_ptr);
		if (oinst_coll_ptr)
		{
		    I_Object_Instance* oinst_ptr = 0;
		    FOR_ALL_ELEMENTS
			(oinst_ptr,
			I_Object_Instance,
			oinst_coll_ptr,
			oinst_cursor)
		    {
			oinst_ptr->set_related_flag (0);
		    }
		}
		is_first_stmt_to_cause_rerelate = FALSE;
	    }
	}
	else
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("Do not recognize CREATE type."));
	    print_create_table_usage ();
	    print_create_rop_ref_id_usage ();
	    print_create_rop_chain_usage ();
	}
    }
    else if (operation_str == insert_string)
    {
	Description into_str;
    stmt_str.parse_token (stmt_cursor, into_str);
	into_str.convert_to_upper_case ();
	if (into_str != "INTO")
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Syntax of 'INSERT' command incorrect - correct syntax is:\n")
		+ "    INSERT  INTO  <obj>  VALUES  (<value>,...)");
	    return FALSE;
	}
	
	Description obj_name_str;
    stmt_str.parse_token (stmt_cursor, obj_name_str);
	obj_name_str.convert_to_upper_case ();
	mc_dbms_Set <I_Object*>* obj_coll_ptr
	    = I_Object::find_Object_by_key_letter
		(GS_gen_sim_db_ptr, obj_name_str.char_ptr ());


	if (! obj_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_import::import_sql_statement ():  Creation of I_Object collection in find returned 0."));
	    return FALSE;
	}

	if (obj_coll_ptr->cardinality () < 1)
	{
	    Description err_msg ("Object '");
		err_msg += obj_name_str;
		err_msg += "' Unknown.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    delete obj_coll_ptr;
	    return FALSE;
	}

	if (obj_coll_ptr->cardinality () > 1)
	{
	    LOG_ERROR ((L_log_string,
		"GS_import::import_sql_statement ():  Reference side I_Object Collection resulted in more than one instance! - continuing with one of the instances."));
	}

	I_Object* obj_ptr = obj_coll_ptr->pick ();
	delete obj_coll_ptr;
	if (! obj_ptr)
	{
	    Description err_msg ("Object '");
		err_msg += obj_name_str;
		err_msg += "' not a valid object in the DB.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    return FALSE;
	}
	
	Description values_str;
    stmt_str.parse_token (stmt_cursor, values_str);
	values_str.convert_to_upper_case ();
	if (values_str != values_string)
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Syntax of 'INSERT' command incorrect - correct syntax is:\n")
		+ "    INSERT  INTO  <obj>  VALUES  (<value>,...)");
	    return FALSE;
	}
	
	I_Object_Instance* oinst_ptr = 0;
	if (obj_ptr->get_Object_Instance_R2001_coll_ptr ()->cardinality () < 1)
	{
	    //  No instances exist yet in the DB for this object type.  Create
	    //    a new segment and place this first instance in that segment.
	    //
	    mc_dbms_segment* oinst_segment_ptr
		= GS_gen_sim_db_ptr->create_segment ();
	    oinst_ptr = I_Object_Instance::create (oinst_segment_ptr);
	}
	else
	{
	    //  One or more instances already exists in the DB for this
	    //    object type.  New this new instance in the same segment
	    //    as the other instances.
	    //
	    oinst_ptr = I_Object_Instance::create (mc_dbms_segment::of
		(obj_ptr->get_Object_Instance_R2001_coll_ptr ()->pick ()));
	}

	if (! oinst_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  Unable to create an instance of 'I_Object_Instance'."));
	    return FALSE;
	}
	oinst_ptr->relate_R2001 (obj_ptr);

    Description dummy;
	stmt_str.parse_token ('(', stmt_cursor, dummy);
	if (stmt_str.char_at (stmt_cursor) != '(')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Syntax of 'INSERT' command incorrect - correct syntax is:\n")
		+ "    INSERT  INTO  <obj>  VALUES  (<value>,...)");
	    return FALSE;
	}
	stmt_cursor++;
	t_uint attr_value_set_cursor = 0;
	Description attr_value_set_str;
    stmt_str.parse_token (')', stmt_cursor, attr_value_set_str, TRUE);
//	    GS_string::GS_IGNORE_WITHIN_TICKS
//	    | GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS));
	if (stmt_str.char_at (stmt_cursor) != ')')
	{
	    GS_ui::inform (UI_INFORM__ERROR, GS_string ("Syntax of 'INSERT' command incorrect - correct syntax is:\n")
		+ "    INSERT  INTO  <obj>  VALUES  (<value>,...)");
	    return FALSE;
	}
	stmt_cursor++;

	mc_dbms_List <I_Attribute*>* attr_coll_ptr
	    = obj_ptr->get_Attribute_R102_coll_ptr ();
	if (! attr_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"GS_import::import_sql_statement ():  Collection associated with rel between O_OBJ & O_ATTR returned 0."));
	    return FALSE;
	}

	unsigned int num_attr_values ;
	for (num_attr_values = 0;
	    attr_value_set_cursor < attr_value_set_str.length ();
	    num_attr_values++)
	{
	    Description attr_value_str;
        attr_value_set_str.parse_token (',', attr_value_set_cursor, attr_value_str, TRUE);
//		GS_string::GS_IGNORE_WITHIN_TICKS
//		| GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS));
	    if (attr_value_set_str.char_at (attr_value_set_cursor) == ',')
	    {
			attr_value_set_cursor++;
	    }

	    if (attr_value_str.length() == 0)
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("INSERT statement is missing value."));
		return FALSE;
	    }
	    else
	    {
		if (num_attr_values >= attr_coll_ptr->cardinality ())
		{
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("INSERT statement has more values than attributes."));
		    return FALSE;
		}

		I_Attribute* attr_ptr
		    = obj_ptr->get_Attribute_R102_coll_ptr ()->
			retrieve (num_attr_values);
		if (! attr_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  Unable to access instance of 'I_Attribute'."));
		    return FALSE;
		}
		
		I_Attribute_Instance* ainst_ptr = 0;
		Description attr_name = attr_ptr->get_name ();
		attr_name.convert_to_upper_case ();
		if (attr_ptr->get_name () != descrip_string)
		{
		    //  Create this attribute instance in the same segment
		    //    as the rest of the attribute data (since it will
		    //    be needed in close locality when searching).
		    //
		    ainst_ptr = I_Attribute_Instance::create
			(mc_dbms_segment::of (oinst_ptr),
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		else if (attr_ptr->get_Attribute_Instance_R2002_coll_ptr ()->
		    cardinality () < 1)
		{
		    //  No description attribute instances exist yet in the DB
		    //    for this description attribute.  Create a new segment
		    //    and place this first description attribute instance
		    //    in that segment.  This is done since descriptions
		    //    are not used for searching and are best stored
		    //    separately from the rest of the data so they do not
		    //    spread the data out.
		    //
		    mc_dbms_segment* descrip_ainst_segment_ptr
			= GS_gen_sim_db_ptr->create_segment ();
		    ainst_ptr = I_Attribute_Instance::create
			(descrip_ainst_segment_ptr,
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		else
		{
		    //  One or more description attribute instances already
		    //    exists in the DB for this description attribute.
		    //    New this new description attribute instance in the
		    //    same segment as the other description attribute
		    //    instances.
		    //
		    ainst_ptr = I_Attribute_Instance::create
			(mc_dbms_segment::of (attr_ptr->
			    get_Attribute_Instance_R2002_coll_ptr ()->pick ()),
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		if (! ainst_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  Unable to create an instance of 'I_Attribute_Instance'."));
		    return FALSE;
		}
		ainst_ptr->relate_R2002 (oinst_ptr);
		ainst_ptr->relate_R2002 (attr_ptr);

		I_var* ainst_var_ptr = ainst_ptr->get_var_ptr ();
		if (! ainst_var_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  ainst_var_ptr == 0."));
		    return FALSE;
		}
		
		if (ainst_var_ptr->get_boolean_var_ptr ())
		{                                                 
		    attr_value_str.convert_to_upper_case ();
		    if ((attr_value_str == false_string) || (attr_value_str == zero_string))
		    {
			ainst_var_ptr->get_boolean_var_ptr ()->
			    set_value (FALSE);
		    }
		    else if
			((attr_value_str == true_string) || (attr_value_str == num_one_string))
		    {
			ainst_var_ptr->get_boolean_var_ptr ()->
			    set_value (TRUE);
		    }
		    else
		    {
			GS_ui::inform (UI_INFORM__ERROR,
			    GS_string("Do NOT recognize BOOLEAN value."));
			return FALSE;
		    }
		}
		else if (ainst_var_ptr->get_integer_var_ptr ())
		{
		    for (unsigned int i = 0;
			i < attr_value_str.length ();
			i++)
		    {
			if (i == 0)
			{
			    if (!
				(vcharIsDigit (attr_value_str.char_at(i))
				||
				(attr_value_str.char_at(i) == '-')))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for INTEGER field in INSERT statement does not begin with a '-' or digit character."));
				return FALSE;
			    }
			}
			else
			{
			    if (! vcharIsDigit (attr_value_str.char_at(i)))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for INTEGER field in INSERT statement contains a non-digit character."));
				return FALSE;
			    }
			}
		    }
		    t_long attr_value_int = vnumParseLong( attr_value_str.char_ptr(), 0);
		    ainst_var_ptr->get_integer_var_ptr ()->
				set_value (attr_value_int);
		}
		else if (ainst_var_ptr->get_real_var_ptr ())
		{
		    for (unsigned int i = 0;
			i < attr_value_str.length ();
			i++)
		    {
			if (i == 0)
			{
			    if (!
				(vcharIsDigit (attr_value_str.char_at(i))
				||
				(attr_value_str.char_at(i) == '.')
				||
				(attr_value_str.char_at(i) == '-')))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for REAL field in INSERT statement does not begin with a '-', '.', or digit character."));
				return FALSE;
			    }
			}
			else
			{
			    if (!
				(vcharIsDigit (attr_value_str.char_at(i))
				||
				(attr_value_str.char_at(i) == '.')))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for REAL field in INSERT statement contains a non-digit character."));
				return FALSE;
			    }
			}
		    }
		    double attr_value_real = vnumParseFloat(attr_value_str.char_ptr(), 0);
		    ainst_var_ptr->get_real_var_ptr ()->
				set_value (attr_value_real);
		}
		else if (ainst_var_ptr->get_string_var_ptr ())
		{
		    if (attr_value_str.char_at(0) != '\'')
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string("Value for STRING field in INSERT statement does NOT  BEGIN  with a tick character."));
			return FALSE;
		    }
		    if (attr_value_str.char_at(attr_value_str.length () - 1) != '\'')
		    {
			GS_ui::inform (UI_INFORM__ERROR, GS_string("Value for STRING field in INSERT statement does NOT  END  with a tick character."));
			return FALSE;
		    }

		    Description tickless_attr_value_str;
			attr_value_str.convert_delimited_string ('\'', TRUE, tickless_attr_value_str );
		    ainst_var_ptr->get_string_var_ptr ()->
				set_value (tickless_attr_value_str);
		}
		else if (ainst_var_ptr->get_unique_id_var_ptr ())
		{
		    for (unsigned int i = 0;
			i < attr_value_str.length ();
			i++)
		    {
			if (i == 0)
			{
			    if (!
				(vcharIsDigit (attr_value_str.char_at(i))
				||
				(attr_value_str.char_at(i) == '-')))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for UNIQUE_ID field in INSERT statement does not begin with a '-' or digit character."));
				return FALSE;
			    }
			}
			else
			{
			    if (! vcharIsDigit (attr_value_str.char_at(i)))
			    {
				GS_ui::inform (UI_INFORM__ERROR,
				    GS_string("Value for UNIQUE_ID field in INSERT statement contains a non-digit character."));
				return FALSE;
			    }
			}
		    }
		    unsigned long attr_value_int = vnumParseULong( attr_value_str.char_ptr(), 0);
		    if ( (attr_value_int & 0xf0000000) != 0 )
		    {
			GS_ui::inform (UI_INFORM__WARNING,
			    GS_string("Value for UNIQUE_ID field in INSERT statement contains a non-zero domain code (most significant 4 bits)."));
			attr_value_int &= 0x0fffffff; // mask off non-zero domain
		    }
		    // or-in domain code entered by user.
		    unsigned long domain_code = GS_domain_code;
		    attr_value_int |= domain_code << 28;
		    ainst_var_ptr->get_unique_id_var_ptr ()->
			set_value (attr_value_int);
		}
		else
		{
		    LOG_ERROR ((L_log_string,
			"GS_import::import_sql_statement ():  I_Attribute data type NOT recognized."));
		    return FALSE;
		}
	    }
	}


	if (num_attr_values > attr_coll_ptr->cardinality ())
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("INSERT statement has more values than attributes."));
	    return FALSE;
	}
	else if (num_attr_values < attr_coll_ptr->cardinality ())
	{
	    for (;
		num_attr_values < attr_coll_ptr->cardinality ();
		num_attr_values++)
	    {
		I_Attribute* attr_ptr
		    = obj_ptr->get_Attribute_R102_coll_ptr ()->
			retrieve (num_attr_values);
		if (! attr_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  Unable to access instance of 'I_Attribute'."));
		    return FALSE;
		}
		
		I_Attribute_Instance* ainst_ptr = 0;
		Description attr_name = attr_ptr->get_name ();
		attr_name.convert_to_upper_case ();
		if (attr_ptr->get_name () != descrip_string)
		{
		    //  Create this attribute instance in the same segment
		    //    as the rest of the attribute data (since it will
		    //    be needed in close locality when searching).
		    //
		    ainst_ptr = I_Attribute_Instance::create
			(mc_dbms_segment::of (oinst_ptr),
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		else if (attr_ptr->get_Attribute_Instance_R2002_coll_ptr ()->
		    cardinality () < 1)
		{
		    //  No description attribute instances exist yet in the DB
		    //    for this description attribute.  Create a new segment
		    //    and place this first description attribute instance
		    //    in that segment.  This is done since descriptions
		    //    are not used for searching and are best stored
		    //    separately from the rest of the data so they do not
		    //    spread the data out.
		    //
		    mc_dbms_segment* descrip_ainst_segment_ptr
			= GS_gen_sim_db_ptr->create_segment ();
		    ainst_ptr = I_Attribute_Instance::create
			(descrip_ainst_segment_ptr,
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		else
		{
		    //  One or more description attribute instances already
		    //    exists in the DB for this description attribute.
		    //    New this new description attribute instance in the
		    //    same segment as the other description attribute
		    //    instances.
		    //
		    ainst_ptr = I_Attribute_Instance::create
			(mc_dbms_segment::of (attr_ptr->
			    get_Attribute_Instance_R2002_coll_ptr ()->pick ()),
			attr_ptr->get_core_data_type (),
			attr_ptr->get_user_data_type (), GS_domain_code);
		}
		if (! ainst_ptr)
		{
		    LOG_ERROR ((L_log_string,
			"MC_DBMS_rel_desc::MC_DBMS_rel_desc ():  Unable to create an instance of 'I_Attribute_Instance'."));
		    return FALSE;
		}
		ainst_ptr->relate_R2002 (oinst_ptr);
		ainst_ptr->relate_R2002 (attr_ptr);
	    }
	}


	//  If this is the first statement processed, then reset all related
	//    flags so that all instance relationships will be re-calculated
	//
	if (is_first_stmt_to_cause_rerelate)
	{
	    mc_dbms_List<I_Object_Instance*>* oinst_coll_ptr =
		I_Object_Instance::get_class_extent_ptr (GS_gen_sim_db_ptr);
	    if (oinst_coll_ptr)
	    {
		I_Object_Instance* oinst_ptr = 0;
		FOR_ALL_ELEMENTS
		    (oinst_ptr,
		    I_Object_Instance,
		    oinst_coll_ptr,
		    oinst_cursor)
		{
		    oinst_ptr->set_related_flag (0);
		}
	    }
	    is_first_stmt_to_cause_rerelate = FALSE;
	}
    }
    else if (operation_str == dash_dash_string)
    {
    	//  SQL COMMENT - DO NOTHING
	//
    }
    else
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Do not recognize SQL statement."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	    "End  GS_import::import_sql_statement (FALSE)."));
	return FALSE;
    }


    stmt_str.consume_white_space (stmt_cursor);
    if (stmt_cursor < stmt_str.length ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Unexpected text at end of SQL Statement (Check for missing ';' on previous statement)."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	    "End  GS_import::import_sql_statement (FALSE)."));
	return FALSE;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"End  GS_import::import_sql_statement (TRUE)."));
    return TRUE;
}
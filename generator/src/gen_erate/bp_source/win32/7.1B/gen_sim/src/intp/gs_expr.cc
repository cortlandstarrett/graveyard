/*========================================================================
 *
 * File:      $RCSfile: gs_expr.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:29 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <ctype.h>

#include <gs_ui.hh>
#include <gs_expr.hh>
#include <gs_stack.hh>
#include <u_string.hh>
#include <gs_sub.hh>

#include <i_clock.hh>

#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#else
#include <u_trace.hh>
#include <u_report.hh>
#include <u_error.hh>
#endif




void
GS_expression::interpret_stmt__assign (const Description& p_stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_stmt__assign (p_stmt_str=\"%s\").",
	p_stmt_str.char_ptr ()));


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


    Description assign_str;
    stmt_str.parse_token (stmt_cursor, assign_str);
    assign_str.convert_to_upper_case ();
    if ((assign_str != assign_string) && (assign_str != dot_assign))
    {
        LOG_ERROR ((L_log_string,
	    "End #1:  GS_expression::interpret_stmt__assign ():  Called for a statement which is NOT an 'ASSIGN' statement.  Ignoring line and going on."));
        return;
    }


    Description lvalue_str;
    stmt_str.parse_token__lvalue (stmt_cursor, lvalue_str);
    if (!stmt_str.compare_first('=', stmt_cursor))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Malformed ASSIGN statement - missing '=' sign."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_expression::interpret_stmt__assign ()."));
	return;
    }


    //  Move past the '=' sign in the ASSIGN statement.
    //
    stmt_cursor++;


    //  Interpret the expression which follows the '=' sign.
    //
    Description expression_str;
    stmt_str.parse_to_end (stmt_cursor, expression_str);
    GS_var_si rvalue_var_si;
    interpret_frag__expression (expression_str, rvalue_var_si);
    if ((! rvalue_var_si.get_var_ptr ())
	||
	(rvalue_var_si.get_var_ptr ()->get_core_data_type () == VOID_DATATYPE))
    {
	//  Assume error message already printed.
	//
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_stmt__assign ()."));
	return;
    }


    GS_stack::place_result_in_stack_var (lvalue_str, &rvalue_var_si);


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #4:  GS_expression::interpret_stmt__assign ()."));
    return;
}





t_boolean
GS_expression::interpret_stmt__if (const Description& stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_stmt__if (p_stmt_str=\"%s\").",
	stmt_str.char_ptr ()));


    //Description stmt_str (p_stmt_str);
	t_uint stmt_cursor = 0;

    Description if_str;
    stmt_str.parse_token ('(', stmt_cursor, if_str);
    if_str.convert_to_upper_case ();
    if ((if_str != if_string) && (if_str != dot_if))
    {
        LOG_ERROR ((L_log_string,
	    "End #1:  GS_expression::interpret_stmt__if () called for a statement which is NOT an 'IF' statement.  Ignoring line and going on."));
        return FALSE;
    }


    //  Interpret the expression.
    //
    Description expression_str;
    stmt_str.parse_token__parened_str (stmt_cursor, expression_str);
    GS_var_si rvalue_var_si;
    interpret_frag__expression (expression_str, rvalue_var_si);
    if ((! rvalue_var_si.get_var_ptr ())
	||
	(rvalue_var_si.get_var_ptr ()->get_core_data_type () == VOID_DATATYPE))
    {
	//  Assume error message already printed.
	//
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_expression::interpret_stmt__if (FALSE)."));
	return FALSE;
    }


    if (rvalue_var_si.get_var_ptr ()->get_core_data_type() != BOOLEAN_DATATYPE)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("IF statement may only contain a BOOLEAN expression."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_stmt__if (FALSE)."));
	return FALSE;
    }


    if (! rvalue_var_si.get_boolean_var_ptr ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error:  Internal BOOLEAN result missing."));
	LOG_ERROR ((L_log_string,
	    "End #4:  GS_expression::interpret_stmt__if (FALSE):  Internal BOOLEAN result missing."));
	return FALSE;
    }


    if (rvalue_var_si.get_boolean_var_ptr ()->get_value ())
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  GS_expression::interpret_stmt__if (TRUE)."));
	return TRUE;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  GS_expression::interpret_stmt__if (FALSE)."));
    return FALSE;
}





t_boolean
GS_expression::interpret_stmt__elif (const Description& stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_stmt__elif (p_stmt_str=\"%s\").",
	stmt_str.char_ptr ()));


    //Description stmt_str (p_stmt_str);
	t_uint stmt_cursor = 0;

    Description elif_str;
    stmt_str.parse_token ('(', stmt_cursor, elif_str);
    elif_str.convert_to_upper_case ();
    if ((elif_str != elif_string) && (elif_str != dot_elif))
    {
        LOG_ERROR ((L_log_string,
	    "End #1:  GS_expression::interpret_stmt__elif () called for a statement which is NOT an 'ELIF' statement."));
        return FALSE;
    }


    //  Interpret the expression.
    //
    Description expression_str;
    stmt_str.parse_token__parened_str (stmt_cursor, expression_str);
    GS_var_si rvalue_var_si;
    interpret_frag__expression (expression_str, rvalue_var_si);
    if ((! rvalue_var_si.get_var_ptr ())
	||
	(rvalue_var_si.get_var_ptr ()->get_core_data_type () == VOID_DATATYPE))
    {
	//  Assume error message already printed.
	//
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_expression::interpret_stmt__elif (FALSE)."));
	return FALSE;
    }


    if (rvalue_var_si.get_var_ptr ()->get_core_data_type() != BOOLEAN_DATATYPE)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("'ELSE IF' statement may only contain a BOOLEAN expression."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_stmt__elif (FALSE)."));
	return FALSE;
    }


    if (! rvalue_var_si.get_boolean_var_ptr ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error:  Internal BOOLEAN result missing."));
	LOG_ERROR ((L_log_string,
	    "End #4:  GS_expression::interpret_stmt__elif (FALSE):  Internal BOOLEAN result missing."));
	return FALSE;
    }


    if (rvalue_var_si.get_boolean_var_ptr ()->get_value ())
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  GS_expression::interpret_stmt__elif (TRUE)."));
	return TRUE;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  GS_expression::interpret_stmt__elif (FALSE)."));
    return FALSE;
}





t_boolean
GS_expression::interpret_stmt__while (const Description& stmt_str)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_stmt__while (p_stmt_str=\"%s\").",
	stmt_str.char_ptr ()));


    //Description stmt_str (p_stmt_str);
	t_uint stmt_cursor = 0;


    Description while_str;
    stmt_str.parse_token ('(', stmt_cursor, while_str);
    while_str.convert_to_upper_case ();
    if ((while_str != while_string) && (while_str != dot_while))
    {
        LOG_ERROR ((L_log_string,
	    "End #1:  GS_expression::interpret_stmt__while () called for a statement which is NOT an 'WHILE' statement.  Ignoring line and going on."));
        return FALSE;
    }


    //  Interpret the expression.
    //
    Description expression_str;
    stmt_str.parse_token__parened_str (stmt_cursor, expression_str);
    GS_var_si rvalue_var_si;
    interpret_frag__expression (expression_str, rvalue_var_si);
    if ((! rvalue_var_si.get_var_ptr ())
	||
	(rvalue_var_si.get_var_ptr ()->get_core_data_type () == VOID_DATATYPE))
    {
	//  Assume error message already printed.
	//
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_expression::interpret_stmt__while (FALSE)."));
	return FALSE;
    }


    if (rvalue_var_si.get_var_ptr ()->get_core_data_type() != BOOLEAN_DATATYPE)
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("WHILE statement may only contain a BOOLEAN expression."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_stmt__while (FALSE)."));
	return FALSE;
    }


    if (! rvalue_var_si.get_boolean_var_ptr ())
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("Internal Error:  Internal BOOLEAN result missing."));
	LOG_ERROR ((L_log_string,
	    "End #4:  GS_expression::interpret_stmt__while (FALSE):  Internal BOOLEAN result missing."));
	return FALSE;
    }


    if (rvalue_var_si.get_boolean_var_ptr ()->get_value ())
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #5:  GS_expression::interpret_stmt__while (TRUE)."));
	return TRUE;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #6:  GS_expression::interpret_stmt__while (FALSE)."));
    return FALSE;
}





void
GS_expression::interpret_frag__expression
    (Description& expression_str, GS_var_si& p_rvalue_var_si)

{

    // This function modifies the parameter 'expression_str' to
    // save making a temporary copy.  The parameter is usually a 
    // temp that's never used.

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_frag__expression (p_expression_str=\"%s\").",
	expression_str.char_ptr ()));


    p_rvalue_var_si.replace_var (new I_void_var ());


    t_uint number_temp_vars_on_stack = 0;


    Description unary_operator_str;

    Description raw_rvalue1_str;
    GS_var_si rvalue1_var_si;

    Description binary_operator_str;

    Description raw_rvalue2_str;
    GS_var_si rvalue2_var_si;


//    Description expression_str (p_expression_str);
	t_uint expression_cursor = 0;
    Description pre_sub_expr_str;
    expression_str.parse_token ('(', expression_cursor, pre_sub_expr_str, TRUE, TRUE);
    t_uint num_subexpressions = 0;
    while ((expression_str.char_at(expression_cursor) == '(') && 
        (num_subexpressions < 2))
    {
        //  Expression contains a sub-expression...
        //
        //  Note:  We only expect 2 subexpressions because we only handle
        //    binary operations.
        //
        num_subexpressions++;
        Description sub_expr_str;
        expression_str.parse_token__parened_str (expression_cursor, sub_expr_str);
        t_boolean end_paren_found = FALSE;
        if (expression_cursor > 0)
        {
            for (int last_char_position = expression_cursor - 1;
            ((last_char_position > 0)
                && (vcharIsWhiteSpace(expression_str.char_at(last_char_position))));
            last_char_position--);
            if (expression_str.char_at(last_char_position) == ')')
            {
                end_paren_found = TRUE;
            }
        }
        if (! end_paren_found)
        {
            GS_ui::inform (UI_INFORM__ERROR,
                GS_string("Unable to find matching ')' character."));
            goto invalid_expression;
        }
        Description post_sub_expr_str;
        expression_str.parse_to_end (expression_cursor, post_sub_expr_str);
        
        GS_var_si sub_expr_rvalue_var_si;
        interpret_frag__expression (sub_expr_str, sub_expr_rvalue_var_si);
        if ((! sub_expr_rvalue_var_si.get_var_ptr ())
            ||
            (sub_expr_rvalue_var_si.get_var_ptr ()->get_core_data_type ()
            == VOID_DATATYPE))
        {
            //  Assume error message already printed.
            //
            LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
                "End #1:  GS_expression::interpret_frag__expression ():  (Sub)Expression evaluates to a VOID."));
            goto invalid_expression;
        }
        
        char temp_var_name_array[32];
        static t_int temp_var_number = 0;
        sprintf (temp_var_name_array, "____sub_expr_var_%08x",
            temp_var_number);
        Description temp_var_name_str(temp_var_name_array);
        temp_var_number++;
        GS_stack::push_var (sub_expr_rvalue_var_si.get_var_ptr (), 
             temp_var_name_str );
        number_temp_vars_on_stack++;
        expression_str = pre_sub_expr_str;
        expression_str += " ";
        expression_str += temp_var_name_str;
        expression_str += " ";
        expression_str += post_sub_expr_str;
        
        //  Look for more sub-expressions in the expression.
        //
        expression_cursor = 0;
        expression_str.parse_token ('(', expression_cursor, pre_sub_expr_str, 
            TRUE, TRUE);
    }


    //  Expression does NOT contain any more sub-expressions.
    //
    expression_cursor = 0;


    //  Try out the first part of the expression and see if it matches any
    //    UNARY operators.
    //
    expression_str.parse_token__unary_op (expression_cursor, unary_operator_str);
    if (unary_operator_str.length() == 0)
    {
	//  First part of expression does NOT match any UNARY operators -
	//    go on.
	//
    }

    else if (unary_operator_str == not_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (! rvalue1_var_si.get_boolean_var_ptr ())
	{
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("NOT operator expects BOOLEAN rvalue."));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #2:  GS_expression::interpret_frag__expression ():  NOT operator expects BOOLEAN rvalue."));
	    goto invalid_expression;
	}
	if (rvalue1_var_si.get_boolean_var_ptr ()->get_value ())
	{
	    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean) FALSE));
	}
	else
	{
	    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean) TRUE));
	}
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_frag__expression ()."));
	goto valid_expression;
    }


    else if (unary_operator_str == empty_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_var_ptr ()->is_empty ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #4:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}
	else if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_empty ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #5:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #6:  GS_expression::interpret_frag__expression ():  EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == not_empty_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_var_ptr ()->is_empty ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #7:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}
	else if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_empty ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #8:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("NOT_EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #9:  GS_expression::interpret_frag__expression ():  NOT_EMPTY operator expects INST_REF or INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == first_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_first ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #10:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("FIRST operator expects INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #11:  GS_expression::interpret_frag__expression ():  EMPTY operator expects INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == not_first_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_first ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #12:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("NOT_FIRST operator expects INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #13:  GS_expression::interpret_frag__expression ():  EMPTY operator expects INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == last_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_last ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #14:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("LAST operator expects INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #15:  GS_expression::interpret_frag__expression ():  EMPTY operator expects INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == not_last_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->is_last ())
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) FALSE));
	    }
	    else
	    {
		p_rvalue_var_si.
		    replace_var (new I_boolean_var ((t_boolean) TRUE));
	    }
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #16:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("NOT_LAST operator expects INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #17:  GS_expression::interpret_frag__expression ():  NOT_LAST operator expects INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == cardinality_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_var_ptr ())
	{
	    p_rvalue_var_si.
		replace_var (new I_integer_var ((t_long) (
		    rvalue1_var_si.get_object_inst_ref_var_ptr ()->
		    cardinality ())));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End 18:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}
	else if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    p_rvalue_var_si.
		replace_var (new I_integer_var ((t_long) (
		    rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->
		    cardinality ())));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #19:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("CARDINALITY operator expects INST_REF or INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #19.5:  GS_expression::interpret_frag__expression ():  CARDINALITY operator expects INST_REF or INST_REF_SET rvalue."));
	goto invalid_expression;
    }

    else if (unary_operator_str == obj_key_letters_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_object_inst_ref_var_ptr ())
	{
	    p_rvalue_var_si.replace_var (new I_string_var
		(rvalue1_var_si.get_object_inst_ref_var_ptr ()->
		get_key_letters_str ()));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #20:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}
	else if (rvalue1_var_si.get_object_inst_ref_set_var_ptr ())
	{
	    p_rvalue_var_si.replace_var (new I_string_var
		(rvalue1_var_si.get_object_inst_ref_set_var_ptr ()->
		get_key_letters_str ()));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #21:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("OBJ_KEY_LETTERS operator expects INST_REF or INST_REF_SET rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #22:  GS_expression::interpret_frag__expression ():  OBJ_KEY_LETTERS operator expects INST_REF or INST_REF_SET rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == initialized_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_var_ptr ())
	{
	    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		rvalue1_var_si.get_var_ptr ()->get_is_initialized ()));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #27:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("INITIALIZED operator expects rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #28:  GS_expression::interpret_frag__expression ():  INITIALIZED operator expects rvalue."));
	goto invalid_expression;
    }


    else if (unary_operator_str == not_initialized_string)
    {
	expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
	interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
	if (rvalue1_var_si.get_var_ptr ())
	{
	    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		(! rvalue1_var_si.get_var_ptr ()->get_is_initialized ())));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #29:  GS_expression::interpret_frag__expression ()."));
	    goto valid_expression;
	}

	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("NOT_INITIALIZED operator expects rvalue."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #30:  GS_expression::interpret_frag__expression ():  NOT_INITIALIZED operator expects rvalue."));
	goto invalid_expression;
    }


    else
    {
	    Description err_msg ("Unary Operator '");
		err_msg += unary_operator_str;
	    err_msg += "' not implemented.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_ERROR ((L_log_string,
	    "End #31:  GS_expression::interpret_frag__expression ():  Unary Operator not implemented."));
	goto invalid_expression;
    }




    //  Expression is NOT a UNARY OPERATION - must be either a stand alone
    //    value or a BINARY expression.
    //
    expression_str.parse_token__rvalue (expression_cursor, raw_rvalue1_str);
    interpret_frag__rvalue (raw_rvalue1_str, rvalue1_var_si);
    if ((! rvalue1_var_si.get_var_ptr ())
	||
	(rvalue1_var_si.get_var_ptr ()->get_core_data_type() == VOID_DATATYPE))
    {
	GS_ui::inform (UI_INFORM__ERROR,
	    GS_string("First operand has invalid type."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #32:  GS_expression::interpret_frag__expression ():  First operand has invalid type."));
	goto invalid_expression;
    }


    expression_str.consume_white_space (expression_cursor);
    if (expression_cursor >= expression_str.length ())
    {
	//  Expression string is made up of only an rvalue.
	//
	p_rvalue_var_si.replace_var
	    (rvalue1_var_si.get_var_ptr ());
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #33:  GS_expression::interpret_frag__expression ()."));
	goto valid_expression;
    }


    expression_str.parse_token__binary_op (expression_cursor, binary_operator_str);
    if (binary_operator_str.length() == 0)
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Binary operator is invalid."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #34:  GS_expression::interpret_frag__expression ():  Binary operator is invalid."));
	goto invalid_expression;
    }


    expression_str.parse_token__rvalue (expression_cursor, raw_rvalue2_str);
    interpret_frag__rvalue (raw_rvalue2_str, rvalue2_var_si);
    if ((! rvalue2_var_si.get_var_ptr ())
	||
	(rvalue2_var_si.get_var_ptr ()->get_core_data_type() == VOID_DATATYPE))
    {
	GS_ui::inform (UI_INFORM__ERROR, GS_string("Second operand has invalid type."));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #35:  GS_expression::interpret_frag__expression ():  Second operand has invalid type."));
	goto invalid_expression;
    }


    expression_str.consume_white_space (expression_cursor);
    if (expression_cursor < expression_str.length ())
    {
	//  Expression string is made up of only an rvalue.
	//
	Description rest_str;
    expression_str.parse_to_end (expression_cursor, rest_str);
		Description err_msg ("Extra characters '");
		err_msg += rest_str;
		err_msg += "' after binary operation.  Check to make sure expression is completely parenthesized.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	goto invalid_expression;
    }


    switch (rvalue1_var_si.get_var_ptr ()->get_core_data_type ())
    {
    case BOOLEAN_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case BOOLEAN_DATATYPE:
	    if (binary_operator_str == and_string)
	    {
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_boolean_var_ptr ()->get_value ()
		    && rvalue2_var_si.get_boolean_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "BOOLEAN   AND   BOOLEAN"));
		goto valid_expression;
	    }
	    else if (binary_operator_str == or_string)
	    {
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_boolean_var_ptr ()->get_value ()
		    || rvalue2_var_si.get_boolean_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "BOOLEAN   OR   BOOLEAN"));
		goto valid_expression;
	    }
	    else if (binary_operator_str == equal_equal_string)
	    {
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_boolean_var_ptr ()->get_value ()
		    == rvalue2_var_si.get_boolean_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "BOOLEAN   ==   BOOLEAN"));
		goto valid_expression;
	    }
	    else if (binary_operator_str == bang_equal_string)
	    {
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_boolean_var_ptr ()->get_value ()
		    != rvalue2_var_si.get_boolean_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "BOOLEAN   !=   BOOLEAN"));
		goto valid_expression;
	    }
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("BOOLEAN   ????   BOOLEAN"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"BOOLEAN   ????   BOOLEAN"));
	    goto invalid_expression;

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("BOOLEAN   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"BOOLEAN   ????   ????"));
	    goto invalid_expression;
	}


    case INTEGER_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case INTEGER_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '+':
		p_rvalue_var_si.replace_var (new I_integer_var ((t_long)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    + rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   +   INTEGER"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_integer_var ((t_long)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    - rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   -   INTEGER"));
		goto valid_expression;

	    case '*':
		p_rvalue_var_si.replace_var (new I_integer_var ((t_long)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    * rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   *   INTEGER"));
		goto valid_expression;

	    case '/':
		if (rvalue2_var_si.get_integer_var_ptr()->get_value () != 0)
		{
		    p_rvalue_var_si.replace_var (new I_integer_var ((t_long)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			/ rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   /   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_integer_var ((t_long) 0));
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   /   INTEGER=0"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   /   INTEGER=0"));
		goto invalid_expression;

	    case '%':
		if (rvalue2_var_si.get_integer_var_ptr()->get_value () != 0)
		{
		    p_rvalue_var_si.replace_var (new I_integer_var ((t_long)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			% rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   %   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_integer_var ((t_long) 0));
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   %   INTEGER=0"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   %   INTEGER=0"));
		goto invalid_expression;

	    case '<':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			<= rvalue2_var_si.get_integer_var_ptr()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   <=   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    < rvalue2_var_si.get_integer_var_ptr ()->get_value())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   <   INTEGER"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			== rvalue2_var_si.get_integer_var_ptr()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   ==   INTEGER"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   =???   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   =???   INTEGER"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_integer_var_ptr()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   !=   INTEGER"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   !???   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   !???   INTEGER"));
		goto invalid_expression;

	    case '>':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			>= rvalue2_var_si.get_integer_var_ptr()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   >=   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    > rvalue2_var_si.get_integer_var_ptr()->
		    get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   >   INTEGER"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   ????   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   ????   INTEGER"));
		goto invalid_expression;
	    }

	case REAL_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '+':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    + rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   +   REAL"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    - rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   -   REAL"));
		goto valid_expression;

	    case '*':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    * rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   *   REAL"));
		goto valid_expression;

	    case '/':
		if (rvalue2_var_si.get_real_var_ptr ()->get_value () != 0.0)
		{
		    p_rvalue_var_si.replace_var (new I_real_var ((t_double)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			/ rvalue2_var_si.get_real_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   /   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_real_var ((t_double) 0.0));
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   /   REAL=0.0"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   /   REAL=0.0"));
		goto invalid_expression;

	    case '<':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			<= rvalue2_var_si.get_real_var_ptr()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   <=   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    < rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   <   REAL"));
		goto valid_expression;

	    case '=':
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    == rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   ==   REAL"));
		goto valid_expression;

	    case '!':
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    != rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   !=   REAL"));
		goto valid_expression;

	    case '>':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			>= rvalue2_var_si.get_real_var_ptr()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   >=   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_integer_var_ptr ()->get_value ()
		    > rvalue2_var_si.get_real_var_ptr()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   >   REAL"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   ????   REAL"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   ????   REAL"));
		goto invalid_expression;
	    }

	case UNIQUE_ID_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			== rvalue2_var_si.get_unique_id_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   ==   UNIQUE_ID"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("INTEGER   =???   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   =???   UNIQUE_ID"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_integer_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_unique_id_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   !=   UNIQUE_ID"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("INTEGER   !???   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   !???   UNIQUE_ID"));
		goto invalid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("INTEGER   ????   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   ????   UNIQUE_ID"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("INTEGER   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"INTEGER   ????   ????"));
	    goto invalid_expression;
	}


    case REAL_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case INTEGER_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '+':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    + rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   +   INTEGER"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    - rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   -   INTEGER"));
		goto valid_expression;

	    case '*':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    * rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   *   INTEGER"));
		goto valid_expression;

	    case '/':
		if (rvalue2_var_si.get_integer_var_ptr()->get_value () != 0)
		{
		    p_rvalue_var_si.replace_var (new I_real_var ((t_double)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			/ rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   /   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_real_var ((t_double) 0.0));
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   /   INTEGER=0"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   /   INTEGER=0"));
		goto invalid_expression;

	    case '<':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			<= rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   <=   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    < rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   <   INTEGER"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			== rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   ==   INTEGER"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   =???   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   =???   INTEGER"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   !=   INTEGER"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   !???   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   !???   INTEGER"));
		goto invalid_expression;

	    case '>':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			>= rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   >=   INTEGER"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    > rvalue2_var_si.get_integer_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   >   INTEGER"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   ????   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   ????   INTEGER"));
		goto invalid_expression;
	    }

	case REAL_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '+':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    + rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   +   REAL"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    - rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   -   REAL"));
		goto valid_expression;

	    case '*':
		p_rvalue_var_si.replace_var (new I_real_var ((t_double)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    * rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   *   REAL"));
		goto valid_expression;

	    case '/':
		if (rvalue2_var_si.get_real_var_ptr ()->get_value () != 0.0)
		{
		    p_rvalue_var_si.replace_var (new I_real_var ((t_double)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			/ rvalue2_var_si.get_real_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   /   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_real_var ((t_double) 0.0));
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   /   REAL=0.0"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   /   REAL=0.0"));
		goto invalid_expression;

	    case '<':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			<= rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   <=   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    < rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   <   REAL"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			== rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   ==   REAL"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   =???   REAL"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   =???   REAL"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   !=   REAL"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   !???   REAL"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   !???   REAL"));
		goto invalid_expression;

	    case '>':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_real_var_ptr ()->get_value ()
			>= rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"REAL   >=   REAL"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_real_var_ptr ()->get_value ()
		    > rvalue2_var_si.get_real_var_ptr ()->get_value ())));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   >   REAL"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   ????   REAL"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "REAL   ????   REAL"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"REAL   ????   ????"));
	    goto invalid_expression;
	}


    case STRING_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case STRING_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '+':
			{
			Description tmp_str(rvalue1_var_si.get_string_var_ptr ()->get_value ());
			tmp_str += rvalue2_var_si.get_string_var_ptr ()->get_value ();
		p_rvalue_var_si.replace_var (new I_string_var(tmp_str));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   +   STRING"));
		goto valid_expression;
			}

	    case '<':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_string_var_ptr ()->get_value ().
			compare (rvalue2_var_si.get_string_var_ptr ()->
			get_value ()) <= 0)));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"STRING   <=   STRING"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_string_var_ptr ()->get_value ().
		    compare (rvalue2_var_si.get_string_var_ptr ()->
		    get_value ()) < 0)));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   <   STRING"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_string_var_ptr ()->get_value ()
			== rvalue2_var_si.get_string_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"STRING   ==   STRING"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("STRING   =???   STRING"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   =???   STRING"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_string_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_string_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"STRING   !=   STRING"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR, GS_string("STRING   !???   STRING"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   !???   STRING"));
		goto invalid_expression;

	    case '>':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_string_var_ptr ()->get_value ().
			compare (rvalue2_var_si.get_string_var_ptr ()->
			get_value ()) >= 0)));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"STRING   >=   STRING"));
		    goto valid_expression;
		}
		p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
		    (rvalue1_var_si.get_string_var_ptr ()->get_value ().
		    compare (rvalue2_var_si.get_string_var_ptr ()->
		    get_value ()) > 0)));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   >   STRING"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("STRING   ????   STRING"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "STRING   ????   STRING"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("STRING   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"STRING   ????   ????"));
	    goto invalid_expression;
	}

    case UNIQUE_ID_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case UNIQUE_ID_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_unique_id_var_ptr ()->get_value ()
			== rvalue2_var_si.get_unique_id_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"UNIQUE_ID   ==   UNIQUE_ID"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("UNIQUE_ID   =???   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "UNIQUE_ID   =???   UNIQUE_ID"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_unique_id_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_unique_id_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"UNIQUE_ID   !=   UNIQUE_ID"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("UNIQUE_ID   !???   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "UNIQUE_ID   !???   UNIQUE_ID"));
		goto invalid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("UNIQUE_ID   ????   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "UNIQUE_ID   ????   UNIQUE_ID"));
		goto invalid_expression;
	    }

	case INTEGER_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_unique_id_var_ptr ()->get_value ()
			== rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"UNIQUE_ID   ==   INTEGER"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("UNIQUE_ID   =???   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "UNIQUE_ID   =???   INTEGER"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_unique_id_var_ptr ()->get_value ()
			!= rvalue2_var_si.get_integer_var_ptr ()->
			get_value ())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"INTEGER   !=   UNIQUE_ID"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("INTEGER   !???   UNIQUE_ID"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "INTEGER   !???   UNIQUE_ID"));
		goto invalid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("REAL   ????   INTEGER"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "UNIQUE_ID   ????   INTEGER"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("UNIQUE_ID   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"UNIQUE_ID   ????   ????"));
	    goto invalid_expression;
	}
	break;

    case OBJECT_INST_REF_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case OBJECT_INST_REF_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '|':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "|"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   |   OBJECT_INST_REF"));
		goto valid_expression;

	    case '&':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "&"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   &   OBJECT_INST_REF"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "-"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   -   OBJECT_INST_REF"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var
			((t_boolean) ((*(rvalue1_var_si.get_var_ptr ()))
			== (*(rvalue2_var_si.get_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"OBJECT_INST_REF   ==   OBJECT_INST_REF"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF   =???   OBJECT_INST_REF"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   =???   OBJECT_INST_REF"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var
			((t_boolean) (! ((*(rvalue1_var_si.get_var_ptr ()))
			== (*(rvalue2_var_si.get_var_ptr ()))))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"OBJECT_INST_REF   !=   OBJECT_INST_REF"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF   !???   OBJECT_INST_REF"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   !???   OBJECT_INST_REF"));
		goto invalid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF   ????   OBJECT_INST_REF"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   ????   OBJECT_INST_REF"));
		goto invalid_expression;
	    }

	case OBJECT_INST_REF_SET_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '|':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "|"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   |   OBJECT_INST_REF_SET"));
		goto valid_expression;
	    
	    case '&':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "&"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   &   OBJECT_INST_REF_SET"));
		goto valid_expression;
	    
	    case '-':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "-"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   -   OBJECT_INST_REF_SET"));
		goto valid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF   ????   OBJECT_INST_REF_SET"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF   ????   OBJECT_INST_REF_SET"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("OBJECT_INST_REF   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"OBJECT_INST_REF   ????   ????"));
	    goto invalid_expression;
	}

    case OBJECT_INST_REF_SET_DATATYPE:
	switch (rvalue2_var_si.get_var_ptr ()->get_core_data_type ())
	{
	case OBJECT_INST_REF_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '|':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "|"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   |   OBJECT_INST_REF"));
		goto valid_expression;
	    
	    case '&':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "&"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   &   OBJECT_INST_REF"));
		goto valid_expression;
	    
	    case '-':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_var_ptr (),
		    "-"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   -   OBJECT_INST_REF"));
		goto valid_expression;
	    
	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF_SET   ????   OBJECT_INST_REF"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   ????   OBJECT_INST_REF"));
		goto invalid_expression;
	    }

	case OBJECT_INST_REF_SET_DATATYPE:
	    switch (binary_operator_str.char_at(0))
	    {
	    case '|':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "|"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   |   OBJECT_INST_REF_SET"));
		goto valid_expression;

	    case '&':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "&"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   &   OBJECT_INST_REF_SET"));
		goto valid_expression;

	    case '-':
		p_rvalue_var_si.replace_var (new I_object_inst_ref_set_var
		    (rvalue1_var_si.get_object_inst_ref_set_var_ptr (),
		    rvalue2_var_si.get_object_inst_ref_set_var_ptr (),
		    "-"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   -   OBJECT_INST_REF_SET"));
		goto valid_expression;

	    case '=':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var
			((t_boolean) ((*(rvalue1_var_si.get_var_ptr ()))
			== (*(rvalue2_var_si.get_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"OBJECT_INST_REF_SET   ==   OBJECT_INST_REF_SET"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF_SET   =???   OBJECT_INST_REF_SET"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   =???   OBJECT_INST_REF_SET"));
		goto invalid_expression;

	    case '!':
		if (binary_operator_str.char_at(1) == '=')
		{
		    p_rvalue_var_si.replace_var (new I_boolean_var
			((t_boolean) (! ((*(rvalue1_var_si.get_var_ptr ()))
			== (*(rvalue2_var_si.get_var_ptr ()))))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"OBJECT_INST_REF_SET   !=   OBJECT_INST_REF_SET"));
		    goto valid_expression;
		}
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF_SET   !???   OBJECT_INST_REF_SET"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   !???   OBJECT_INST_REF_SET"));
		goto invalid_expression;

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("OBJECT_INST_REF_SET   ????   OBJECT_INST_REF_SET"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "OBJECT_INST_REF_SET   ????   OBJECT_INST_REF_SET"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR,
		GS_string("OBJECT_INST_REF_SET   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"OBJECT_INST_REF_SET   ????   ????"));
	    goto invalid_expression;
	}

    case MAPPING_INST_DATATYPE:
	switch (rvalue1_var_si.get_var_ptr ()->get_user_data_type ())
	{
	case USER_DEFINED_USERDATATYPE:
	    switch (rvalue2_var_si.get_var_ptr ()->get_user_data_type ())
	    {
	    case USER_DEFINED_USERDATATYPE:
		switch (binary_operator_str.char_at(0))
		{
		case '<':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_mapping_inst_var_ptr ()))
			    <=
			    (*(rvalue2_var_si.get_mapping_inst_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   <=   USER_DEFINED"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var
			(new I_boolean_var ((t_boolean)
			((*(rvalue1_var_si.get_mapping_inst_var_ptr ()))
			<
			(*(rvalue2_var_si.get_mapping_inst_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   <   USER_DEFINED"));
		    goto valid_expression;

		case '=':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   ==   USER_DEFINED"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("USER_DEFINED   =???   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   =???   USER_DEFINED"));
		    goto invalid_expression;

		case '!':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    (! ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ()))))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   !=   USER_DEFINED"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("USER_DEFINED   !???   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   !???   USER_DEFINED"));
		    goto invalid_expression;

		case '>':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_mapping_inst_var_ptr ()))
			    >=
			    (*(rvalue2_var_si.get_mapping_inst_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   >=   USER_DEFINED"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var
			(new I_boolean_var ((t_boolean)
			((*(rvalue1_var_si.get_mapping_inst_var_ptr ()))
			>
			(*(rvalue2_var_si.get_mapping_inst_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   >   USER_DEFINED"));
		    goto valid_expression;

		default:
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("USER_DEFINED   ????   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   ????   USER_DEFINED"));
		    goto invalid_expression;
		}

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("USER_DEFINED   ????   ????"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "USER_DEFINED   ????   ????"));
		goto invalid_expression;
	    }

	case DATE_USERDATATYPE:
	    switch (rvalue2_var_si.get_var_ptr ()->get_user_data_type ())
	    {
	    case DATE_USERDATATYPE:
		switch (binary_operator_str.char_at(0))
		{
		case '<':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_date_var_ptr ()))
			    <=
			    (*(rvalue2_var_si.get_date_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "DATE   <=   DATE"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var
			(new I_boolean_var ((t_boolean)
			((*(rvalue1_var_si.get_date_var_ptr ()))
			<
			(*(rvalue2_var_si.get_date_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"DATE   <   DATE"));
		    goto valid_expression;

		case '=':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "DATE   ==   DATE"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("DATE   =???   DATE"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"DATE   =???   DATE"));
		    goto invalid_expression;

		case '!':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    (! ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ()))))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "DATE   !=   DATE"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("DATE   !???   DATE"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"DATE   !???   DATE"));
		    goto invalid_expression;

		case '>':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_date_var_ptr ()))
			    >=
			    (*(rvalue2_var_si.get_date_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "DATE   >=   DATE"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var
			(new I_boolean_var ((t_boolean)
			((*(rvalue1_var_si.get_date_var_ptr ()))
			>
			(*(rvalue2_var_si.get_date_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"DATE   >   DATE"));
		    goto valid_expression;

		default:
		    GS_ui::inform (UI_INFORM__ERROR, GS_string("DATE   ????   DATE"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"DATE   ????   DATE"));
		    goto invalid_expression;
		}

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("DATE   ????   ????"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "DATE   ????   ????"));
		goto invalid_expression;
	    }

	case TIMESTAMP_USERDATATYPE:
	    switch (rvalue2_var_si.get_var_ptr ()->get_user_data_type ())
	    {
	    case TIMESTAMP_USERDATATYPE:
		switch (binary_operator_str.char_at(0))
		{
		case '<':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_timestamp_var_ptr ()))
			    <=
			    (*(rvalue2_var_si.get_timestamp_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMESTAMP   <=   TIMESTAMP"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var
			(new I_boolean_var ((t_boolean)
			((*(rvalue1_var_si.get_timestamp_var_ptr ()))
			<
			(*(rvalue2_var_si.get_timestamp_var_ptr ())))));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMESTAMP   <   TIMESTAMP"));
		    goto valid_expression;

		case '=':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMESTAMP   ==   TIMESTAMP"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMESTAMP   =???   TIMESTAMP"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMESTAMP   =???   TIMESTAMP"));
		    goto invalid_expression;

		case '!':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    (! ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ()))))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMESTAMP   !=   TIMESTAMP"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMESTAMP   !???   TIMESTAMP"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMESTAMP   !???   TIMESTAMP"));
		    goto invalid_expression;

		case '>':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_timestamp_var_ptr ()))
			    >=
			    (*(rvalue2_var_si.get_timestamp_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMESTAMP   >=   TIMESTAMP"));
			goto valid_expression;
		    }
		    p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean)
			(rvalue1_var_si.get_timestamp_var_ptr ()
			> rvalue2_var_si.get_timestamp_var_ptr())));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMESTAMP   >   TIMESTAMP"));
		    goto valid_expression;

		default:
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMESTAMP   ????   TIMESTAMP"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMESTAMP   ????   TIMESTAMP"));
		    goto invalid_expression;
		}

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("TIMESTAMP   ????   ????"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "TIMESTAMP   ????   ????"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("MAPPING_INST   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"MAPPING_INST   ????   ????"));
	    goto invalid_expression;
	}

    case MAPPING_INST_REF_DATATYPE:
	switch (rvalue1_var_si.get_var_ptr ()->get_user_data_type ())
	{
	case USER_DEFINED_USERDATATYPE:
	    switch (rvalue2_var_si.get_var_ptr ()->get_user_data_type ())
	    {
	    case USER_DEFINED_USERDATATYPE:
		switch (binary_operator_str.char_at(0))
		{
		case '=':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   ==   USER_DEFINED"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("USER_DEFINED   =???   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   =???   USER_DEFINED"));
		    goto invalid_expression;

		case '!':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    (! ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ()))))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "USER_DEFINED   !=   USER_DEFINED"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("USER_DEFINED   !???   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   !???   USER_DEFINED"));
		    goto invalid_expression;

		default:
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("USER_DEFINED   ????   USER_DEFINED"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"USER_DEFINED   ????   USER_DEFINED"));
		    goto invalid_expression;
		}

	    default:
		GS_ui::inform (UI_INFORM__ERROR, GS_string("USER_DEFINED   ????   ????"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "USER_DEFINED   ????   ????"));
		goto invalid_expression;
	    }

	case TIMER_INST_REF_USERDATATYPE:
	    switch (rvalue2_var_si.get_var_ptr ()->get_user_data_type ())
	    {
	    case TIMER_INST_REF_USERDATATYPE:
		switch (binary_operator_str.char_at(0))
		{
		case '=':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ())))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMER_INST_REF   ==   TIMER_INST_REF"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMER_INST_REF   =???   TIMER_INST_REF"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMER_INST_REF   =???   TIMER_INST_REF"));
		    goto invalid_expression;

		case '!':
		    if (binary_operator_str.char_at(1) == '=')
		    {
			p_rvalue_var_si.replace_var
			    (new I_boolean_var ((t_boolean)
			    (! ((*(rvalue1_var_si.get_var_ptr ()))
			    ==
			    (*(rvalue2_var_si.get_var_ptr ()))))));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			    "TIMER_INST_REF   !=   TIMER_INST_REF"));
			goto valid_expression;
		    }
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMER_INST_REF   !???   TIMER_INST_REF"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMER_INST_REF   !???   TIMER_INST_REF"));
		    goto invalid_expression;

		default:
		    GS_ui::inform (UI_INFORM__ERROR,
			GS_string("TIMER_INST_REF   ????   TIMER_INST_REF"));
		    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"TIMER_INST_REF   ????   TIMER_INST_REF"));
		    goto invalid_expression;
		}

	    default:
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("TIMER_INST_REF   ????   ????"));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "TIMER_INST_REF   ????   ????"));
		goto invalid_expression;
	    }

	default:
	    GS_ui::inform (UI_INFORM__ERROR, GS_string("MAPPING_INST_REF   ????   ????"));
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"MAPPING_INST_REF   ????   ????"));
	    goto invalid_expression;
	}

    default:
	GS_ui::inform (UI_INFORM__ERROR, GS_string("????   ????   ????"));
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "????   ????   ????"));
	goto invalid_expression;
    }




invalid_expression:
    GS_ui::inform (UI_INFORM__ERROR, GS_string("Invalid operation."));
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"GS_expression::interpret_frag__expression ():  Invalid operation."));




valid_expression:
    if (number_temp_vars_on_stack > 2)
    {
	LOG_ERROR ((L_log_string,
	    "GS_expression::interpret_frag__expression ():  More than 2 temporary variables on stack."));
    }
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"GS_expression::interpret_frag__expression ():  number_temp_vars_on_stack=%d.",
	number_temp_vars_on_stack));
    for (t_uint ii = 0;
	ii < number_temp_vars_on_stack;
	ii++)
    {
	GS_stack_item* si_ptr = GS_stack::pop ();
	if (si_ptr->get_var_si_ptr ())
	{
	    if (! (si_ptr->get_var_si_ptr ()->get_var_name_str ().
		compare_n ("____sub_expr_var_", 17)))
	    {
		LOG_ERROR ((L_log_string,
		    "GS_expression::interpret_frag__expression ():  Un-expected NON-temporary variable on stack."));
	    }
	}
	else
	{
	    LOG_ERROR ((L_log_string,
		"GS_expression::interpret_frag__expression ():  Un-expected NON-variable on stack."));
	}
	delete si_ptr;
    }


    GS_UI_INFORM_START (UI_INFORM__COMP)
        Description err_msg("expression '");
        err_msg += expression_str.char_ptr();
        err_msg += "' ("; 
    	err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
        err_msg += ") = ";
        err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #36:  GS_expression::interpret_frag__expression (core=%d, user=%d).",
	p_rvalue_var_si.get_var_ptr ()->get_core_data_type (),
	p_rvalue_var_si.get_var_ptr ()->get_user_data_type ()));
}





//  An rvalue can be one of the following:
//
//    rcvd_evt.<evt_data_item>
//    param.<param_name>
//    {boolean literal}
//    {integer literal}
//    {real literal}
//    {string literal}
//    [obj_inst_ref_var].<attr>
//    [frag_ref_var].<attr>
//    [data_var]
//
//  where the [xxx] indicates a variable xxx, the <yyy> indicates a
//    relocatable yyy, and {zzz} indicates a literal value.
//

void
GS_expression::interpret_frag__rvalue
    (const Description& raw_rvalue_str, GS_var_si& p_rvalue_var_si)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_expression::interpret_frag__rvalue (p_raw_rvalue_str=\"%s\").",
	raw_rvalue_str.char_ptr ()));


    p_rvalue_var_si.replace_var (new I_void_var ());


//    Description raw_rvalue_str (p_raw_rvalue_str);
	t_uint raw_rvalue_cursor = 0;
    raw_rvalue_str.consume_white_space (raw_rvalue_cursor);
    Description upper_case_rval_str (raw_rvalue_str);
	t_uint upper_case_rval_cursor = 0;
    upper_case_rval_str.convert_to_upper_case ();
    upper_case_rval_str.consume_white_space (upper_case_rval_cursor);


    if (((upper_case_rval_str.length () >= (upper_case_rval_cursor + 8))
	&&
	(vcharCompareBounded(upper_case_rval_str.char_ptr() + upper_case_rval_cursor, rcvd_evt_string.char_ptr(), 8) == 0)
	&&
	((isspace (upper_case_rval_str.char_at(upper_case_rval_cursor + 8)))
	    ||
	    (upper_case_rval_str.char_at(upper_case_rval_cursor + 8) == '.')))
	||
	((upper_case_rval_str.length () >= (upper_case_rval_cursor + 5))
	&&
	(vcharCompareBounded (upper_case_rval_str.char_ptr() + upper_case_rval_cursor, param_string.char_ptr(), 5) == 0)
	&&
	((isspace (upper_case_rval_str.char_at(upper_case_rval_cursor + 5)))
	    ||
	    (upper_case_rval_str.char_at(upper_case_rval_cursor + 5) == '.'))))
    {
	//  Value is a received event data item access OR a parameter access.
	//
	//  Take out all the white space from the name and make the RCVD_EVT
	//    or PARAM keyword all upper case.
	//
	Description keyword_str;
    raw_rvalue_str.parse_token ('.', raw_rvalue_cursor, keyword_str);
	keyword_str.convert_to_upper_case ();
	raw_rvalue_cursor++;
	Description data_item_name_str;
    raw_rvalue_str.parse_token (raw_rvalue_cursor, data_item_name_str);
	Description var_name_str = keyword_str;
	var_name_str += ".";
	var_name_str += data_item_name_str;

	I_var* var_ptr = GS_stack::find_var_ptr (var_name_str);
	if (! var_ptr)
	{
		Description err_msg ("Unable to find '");
		err_msg += var_name_str;
		err_msg += "' on stack.";
	    GS_ui::inform (UI_INFORM__ERROR, err_msg);
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  GS_expression::interpret_frag__rvalue (VOID_DATATYPE)."));
	    return;
	}

	p_rvalue_var_si.replace_var (var_ptr);
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg("rvalue '");
	    err_msg += raw_rvalue_str.char_ptr();
		err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = ";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_expression::interpret_frag__rvalue ()."));
	return;
    }


    if ((upper_case_rval_str.length () >= (upper_case_rval_cursor + 4))
	&&
	(vcharCompareBounded(upper_case_rval_str.char_ptr() + upper_case_rval_cursor, true_string.char_ptr(), 4) == 0)
	&&
	((upper_case_rval_str.length () == (upper_case_rval_cursor + 4))
	||
	((! (isalnum (upper_case_rval_str.char_at(upper_case_rval_cursor + 4))))
	&&
	(upper_case_rval_str.char_at(upper_case_rval_cursor + 4) != '_'))))
    {
	p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean) TRUE));
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg ("rvalue '");
	    err_msg += raw_rvalue_str.char_ptr();
		err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = ";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #3:  GS_expression::interpret_frag__rvalue (BOOLEAN_DATATYPE = TRUE)."));
	return;
    }


    if ((upper_case_rval_str.length () >= (upper_case_rval_cursor + 5))
	&&
	(vcharCompareBounded(upper_case_rval_str.char_ptr() + upper_case_rval_cursor, false_string.char_ptr(), 5) == 0)
	&&
	((upper_case_rval_str.length () == (upper_case_rval_cursor + 5))
	||
	((! (isalnum (upper_case_rval_str.char_at(upper_case_rval_cursor + 5))))
	&&
	(upper_case_rval_str.char_at(upper_case_rval_cursor + 5) != '_'))))
    {
	p_rvalue_var_si.replace_var (new I_boolean_var ((t_boolean) FALSE));
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg("rvalue '");
	    err_msg += raw_rvalue_str.char_ptr();
		err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = "; 
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #4:  GS_expression::interpret_frag__rvalue (BOOLEAN_DATATYPE = FALSE)."));
	return;
    }


    if ((raw_rvalue_str.char_at(raw_rvalue_cursor) == '+') || 
		(raw_rvalue_str.char_at(raw_rvalue_cursor) == '-') || 
		(raw_rvalue_str.char_at(raw_rvalue_cursor) == '.') || 
		(isdigit (raw_rvalue_str.char_at (raw_rvalue_cursor))))
    {
	//  rvalue is a numeric value.
	//
	t_boolean has_dot = FALSE;
	for (t_uint ii = raw_rvalue_cursor;
	    ii < raw_rvalue_str.length ();
	    ii++)
	{
	    //  test to make sure that first character is either '+', '-', '.',
	    //    or a digit and make sure that the subsequent characters are
	    //    either '.' or a digit.
	    //
	    if (! (((ii == raw_rvalue_cursor) &&
		((raw_rvalue_str.char_at(ii) == '+') 
			|| (raw_rvalue_str.char_at(ii) == '-')
		    || (raw_rvalue_str.char_at(ii) == '.')
		    || isdigit (raw_rvalue_str.char_at(ii))))
		||
			((ii != raw_rvalue_cursor ) &&
			((raw_rvalue_str.char_at(ii) == '.')
		    || isdigit (raw_rvalue_str.char_at(ii))))))
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("rvalue is a malformed literal numeric value."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #5:  GS_expression::interpret_frag__rvalue (VOID_DATATYPE):  rvalue is malformed literal numeric value."));
		return;
	    }
	    if (raw_rvalue_str.char_at(ii) == '.')
	    {
		has_dot = TRUE;
	    }
	}
	if (has_dot)
	{
	    t_double tmp_double = vnumParseFloat( 
			raw_rvalue_str.char_ptr()+raw_rvalue_cursor, 0);
	    p_rvalue_var_si.replace_var (new I_real_var (tmp_double));
        GS_UI_INFORM_START (UI_INFORM__COMP)
	    Description err_msg("rvalue '");
		err_msg += raw_rvalue_str;
		err_msg += "' (";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = ";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #6:  GS_expression::interpret_frag__rvalue (REAL_DATATYPE)."));
	    return;
	}
	t_long tmp_long = vnumParseLong( 
		raw_rvalue_str.char_ptr() + raw_rvalue_cursor, 0); 
	p_rvalue_var_si.replace_var (new I_integer_var (tmp_long));
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg ("rvalue '");
	    err_msg += raw_rvalue_str.char_ptr();
		err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = ";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #7:  GS_expression::interpret_frag__rvalue (INTEGER_DATATYPE)."));
	return;
    }


    if (raw_rvalue_str.char_at(raw_rvalue_cursor) == '"')
    {
	//  rvalue is a quoted string.
	//
    Description tmp_str2;
	raw_rvalue_str.parse_token__quoted_str (raw_rvalue_cursor, tmp_str2);
    Description& tmp_str = GS_substitution::substitute_string( tmp_str2, FALSE );
	p_rvalue_var_si.replace_var (new I_string_var (tmp_str));
    GS_UI_INFORM_START (UI_INFORM__COMP)
	Description err_msg ("rvalue '");
	    err_msg += raw_rvalue_str.char_ptr();
		err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
		err_msg += ") = ";
		err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
	GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #8:  GS_expression::interpret_frag__rvalue (STRING_DATATYPE)."));
	return;
    }


    Description var_name_str;
    raw_rvalue_str.parse_token ('.', raw_rvalue_cursor, var_name_str);
    if (raw_rvalue_str.char_at (raw_rvalue_cursor) == '.')
    {
	I_object_inst_ref_var* object_inst_ref_var_ptr
	    = GS_stack::find_object_inst_ref_var_ptr (var_name_str);
	if (object_inst_ref_var_ptr)
	{
	    //  var_name_str holds an object instance reference variable.
	    //
	    raw_rvalue_cursor++;
	    Description attr_name_str;
        raw_rvalue_str.parse_token (raw_rvalue_cursor, attr_name_str);
	    if ((object_inst_ref_var_ptr->is_valid_attr_name (attr_name_str))
		&&
		(object_inst_ref_var_ptr->get_attr_var_ptr (attr_name_str)))
	    {
		p_rvalue_var_si.replace_var
		    (object_inst_ref_var_ptr->get_attr_var_ptr (attr_name_str));
        GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg ("rvalue '");
		    err_msg += raw_rvalue_str; 
			err_msg += "' (";
		    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
		GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #9:  GS_expression::interpret_frag__rvalue ()."));
		return;
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Attribute Not a valid attribute of object."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #10:  GS_expression::interpret_frag__rvalue (VOID_DATATYPE):  Attribute not a valid attribute of object."));
		return;
	    }
	}

	I_frag_ref_var* frag_ref_var_ptr
	    = GS_stack::find_frag_ref_var_ptr (var_name_str.char_ptr());
	if (frag_ref_var_ptr)
	{
	    //  var_name_str holds a fragment variable.
	    //
	    raw_rvalue_cursor++;
	    Description attr_name_str;
        raw_rvalue_str.parse_token (raw_rvalue_cursor, attr_name_str);
	    if ((frag_ref_var_ptr->is_valid_attr_name (attr_name_str))
		&&
		(frag_ref_var_ptr->get_attr_var_ptr (attr_name_str)))
	    {
		p_rvalue_var_si.replace_var
		    (frag_ref_var_ptr->get_attr_var_ptr (attr_name_str));
        GS_UI_INFORM_START (UI_INFORM__COMP)
		Description err_msg("rvalue '");
		    err_msg += raw_rvalue_str;
			err_msg += "' (";
		    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
		GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #11:  GS_expression::interpret_frag__rvalue ()."));
		return;
	    }
	    else
	    {
		GS_ui::inform (UI_INFORM__ERROR,
		    GS_string("Attribute Not a valid attribute of fragment."));
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #12:  GS_expression::interpret_frag__rvalue (VOID_DATATYPE):  Attribute not a valid attribute of fragment."));
		return;
	    }
	}
    }


    //  var_name_str holds a data variable.
    //
    I_var* var_ptr = GS_stack::find_var_ptr (var_name_str.char_ptr());
    if (! var_ptr)
    {
	    Description err_msg ("Unable to find '");
		err_msg += var_name_str;
		err_msg += "' on stack.";
	GS_ui::inform (UI_INFORM__ERROR, err_msg);
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #13:  GS_expression::interpret_frag__rvalue (VOID_DATATYPE)."));
	return;
    }

    p_rvalue_var_si.replace_var (var_ptr);

    GS_UI_INFORM_START (UI_INFORM__COMP);
        Description err_msg("rvalue '");
	    err_msg += raw_rvalue_str;
    	err_msg += "' (";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_data_type_str ();
	    err_msg += ") = ";
	    err_msg += p_rvalue_var_si.get_var_ptr ()->get_value_str ();
    GS_UI_INFORM_END (UI_INFORM__COMP, err_msg);

    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #14:  GS_expression::interpret_frag__rvalue ()."));
    return;
}

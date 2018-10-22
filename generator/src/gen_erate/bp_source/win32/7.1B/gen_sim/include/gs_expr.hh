/*========================================================================
 *
 * File:      $RCSfile: gs_expr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:19 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_EXPR_HH
#define GS_EXPR_HH

#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif


#include <u_string.hh>
#include <gs_stack.hh>




class GS_expression

{
public:
    static void			interpret_stmt__assign
				    (const Description& p_stmt_str);
    static t_boolean		interpret_stmt__if
				    (const Description& p_stmt_str);
    static t_boolean		interpret_stmt__elif
				    (const Description& p_stmt_str);
    static t_boolean		interpret_stmt__while
				    (const Description& p_stmt_str);
    static void			interpret_frag__expression
				    (Description& p_expression_str,
				    GS_var_si& p_rvalue_var_si);
    static void			interpret_frag__rvalue
				    (const Description& p_rvalue_str,
				    GS_var_si& p_rvalue_var_si);
};




#endif

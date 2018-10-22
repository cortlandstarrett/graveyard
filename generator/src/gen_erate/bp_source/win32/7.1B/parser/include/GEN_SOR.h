/*========================================================================
 *
 * File:      $RCSfile: GEN_SOR.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:31 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GEN_SOR_h
#define GEN_SOR_h
/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 100B25
 */
#include "STreeParser.h"

#include "p_symtbl.hh"
#include "tokens.h"
#include "myAST.h"
#include "p_check.hh"
#include "p_error.hh"
#include "P.h"
#include <fstream.h>
typedef char script_var_name[6]; 
typedef AST SORAST;
class Special_Where;

class GEN_SOR : public STreeParser {
protected:
public:
	GEN_SOR();

	void statement(SORASTBase **_root, bool tracex, bool dumpflagx, int actn_type );
	void valid_statement(SORASTBase **_root);
	void assignment_statement(SORASTBase **_root);
	void break_statement(SORASTBase **_root);
	void bridge_statement(SORASTBase **_root);
	void continue_statement(SORASTBase **_root);
	void control_statement(SORASTBase **_root);
	void create_event_statement(SORASTBase **_root);
	void create_object_statement(SORASTBase **_root);
	void delete_statement(SORASTBase **_root);
	void empty_statement(SORASTBase **_root);
	void for_statement(SORASTBase **_root);
	void generate_statement(SORASTBase **_root);
	void if_statement(SORASTBase **_root);
	void relate_statement(SORASTBase **_root);
	void return_statement(SORASTBase **_root);
	void select_statement(SORASTBase **_root);
	void synch_svc_statement(SORASTBase **_root);
	void transform_statement(SORASTBase **_root);
	void unrelate_statement(SORASTBase **_root);
	void while_statement(SORASTBase **_root);
	void event_spec(SORASTBase **_root,  const vchar *event_ref_var  );
	void instance_chain(SORASTBase **_root,  char *card, bool wc  );
	void object_spec(SORASTBase **_root, char *card, SORAST *irv );
	void select_nowhere(SORASTBase **_root, char *card, SORAST *irv  );
	void select_where(SORASTBase **_root, char *card, SORAST *irv  );
	void select_from(SORASTBase **_root, char *card, SORAST *irv  );
	void expr(SORASTBase **_root);
	void sub_expr(SORASTBase **_root);
	void op_and(SORASTBase **_root);
	void op_or(SORASTBase **_root);
	void op_relational(SORASTBase **_root);
	void op_addition(SORASTBase **_root);
	void op_boolean_negation(SORASTBase **_root);
	void op_multiplication(SORASTBase **_root);
	void term(SORASTBase **_root);
	void rval(SORASTBase **_root);
	void constant_value(SORASTBase **_root);
	void enumerator_literal(SORASTBase **_root);
	void attribute_access(SORASTBase **_root);
	void event_data_access(SORASTBase **_root);
	void param_data_access(SORASTBase **_root,  t_boolean is_rval  );
	void transformer_expr(SORASTBase **_root,  vchar **key_lett, vchar **method, bool *instance_based, script_var_name irv_gen_name  );
	void bridge_expr(SORASTBase **_root,  vchar **key_lett, vchar **method  );
	void synch_svc_expr(SORASTBase **_root,  vchar **method  );
	
	public:
	GEN_SOR( P *p_parser, ofstream &p_out_file ):
	parser(p_parser),
	trace(FALSE),
	dumpflag(FALSE),
	actn_inst_num(1), blck_inst_num(1), stmt_inst_num(1),
	rval_inst_num(1), chain_inst_num(1), param_inst_num(1),
	var_inst_num(1), where_inst_num(1), out_file(&p_out_file),
	C_instance_sm(FALSE),
	C_actn_var_name(0),
	C_obj_kl(0),
	C_last_resort_key_letters(0)
	{}
	~GEN_SOR()
	{     
		if ( C_actn_var_name != 0 )
		delete [] C_actn_var_name;
		if ( C_obj_kl != 0 )
		delete [] C_obj_kl;
	}
	void init ( bool p_instance_sm,
	const char *p_actn_var_name,
	const vchar *p_obj_kl )
	{ 
		C_instance_sm = p_instance_sm;

		if ( C_actn_var_name != 0 )
		delete [] C_actn_var_name;
		C_actn_var_name = new char [ strlen(p_actn_var_name) + 1 ];
		strcpy ( C_actn_var_name, p_actn_var_name );

		if ( C_obj_kl != 0 )
		delete [] C_obj_kl;
		C_obj_kl = new vchar [ vcharLength(p_obj_kl) + 1 ];
		vcharCopy ( p_obj_kl, C_obj_kl );

	}
	void next_actn_var_name( script_var_name var_name )
	{
		sprintf (var_name, "a%03d", actn_inst_num);
		actn_inst_num++;
	}
	void next_blck_var_name( script_var_name var_name )
	{
		sprintf (var_name, "b%03d", blck_inst_num);
		blck_inst_num++;
	}
	void next_chain_var_name( script_var_name var_name )
	{
		sprintf (var_name, "c%03d", chain_inst_num);
		chain_inst_num++;
	}
	void next_param_var_name( script_var_name var_name )
	{
		sprintf (var_name, "p%03d", param_inst_num);
		param_inst_num++;
	}
	void next_rval_var_name( script_var_name var_name )
	{
		sprintf (var_name, "r%03d", rval_inst_num);
		rval_inst_num++;
	}
	void next_stmt_var_name( script_var_name var_name )
	{
		sprintf (var_name, "s%03d", stmt_inst_num);
		stmt_inst_num++;
	}
	void next_var_var_name( script_var_name var_name )
	{
		sprintf (var_name, "v%03d", var_inst_num);
		var_inst_num++;
	}
	void next_where_var_name( script_var_name var_name )
	{
		sprintf (var_name, "w%03d", where_inst_num);
		where_inst_num++;
	}

	void new_scope();
	void get_previous_block(script_var_name);
	void get_previous_where(script_var_name);
	void get_previous_param(script_var_name);
	void drop_scope();
	void add_var_to_scope(const vchar *, const vchar *, script_var_name);
	void delete_all_var_from_scope();
	bool is_var_in_scope(const vchar *);
	bool is_var_declared_in_scope(const vchar *);
	bool is_selected (script_var_name);
	void set_var_declared_in_scope(const vchar *);
	void get_gen_name(const vchar *, script_var_name);
	void add_valid_statement(script_var_name);
	vchar* get_key_letters(const vchar *);
	void declare_oir(script_var_name, const vchar *var, const vchar *kl);
	void declare_oirs(script_var_name, const vchar *var, const vchar *kl);
	void declare_ei(script_var_name, const vchar *var);
	void special_where_invokes( Special_Where *sw );

	void panic ( char *msg )
	{ throw msg; }

	void mismatched_range(int looking_for, int upper_token, SORASTBase *found);
	void missing_wildcard();
	void mismatched_token(int looking_for, SORASTBase *found);
	void no_viable_alt(char *rulename, SORASTBase *root);

	protected:
	P *parser;
	bool trace;
	bool dumpflag;
	private:
	int actn_inst_num;
	int blck_inst_num;
	int chain_inst_num;
	int param_inst_num;
	int rval_inst_num;
	int stmt_inst_num;
	int var_inst_num;
	int where_inst_num;
	char *C_actn_var_name;
	vchar *C_obj_kl;
	bool C_instance_sm;
	ofstream *out_file;
	vchar *C_last_resort_key_letters;
};

#endif /* GEN_SOR_h */

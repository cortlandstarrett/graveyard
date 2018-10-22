/*========================================================================
 *
 * File:      $RCSfile: SIM_SOR.h,v $
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
#ifndef SIM_SOR_h
#define SIM_SOR_h
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
#include "vchar.h"
class GS_var_si;
class GS_string;
class I_Object;
class I_Object_Instance;
class I_Related_Object_Instance_Pair;
class I_SM_Evt_Inst;
class I_object_inst_ref_set_var;
class I_event_inst_var;
class Object;
class Relationship;
class Referential_attribute;
class Description;
typedef AST SORAST;

class SIM_SOR : public STreeParser {
protected:
public:
	SIM_SOR();

	void statement(SORASTBase **_root, bool tracex, bool dumpflagx );
	void valid_statement(SORASTBase **_root,  bool interp  );
	void assignment_statement(SORASTBase **_root,  bool interp  );
	void break_statement(SORASTBase **_root,  bool interp  );
	void bridge_statement(SORASTBase **_root,  bool interp  );
	void control_statement(SORASTBase **_root,  bool interp  );
	void continue_statement(SORASTBase **_root,  bool interp  );
	void create_event_statement(SORASTBase **_root,  bool interp  );
	void create_object_statement(SORASTBase **_root,  bool interp  );
	void delete_statement(SORASTBase **_root,  bool interp  );
	void empty_statement(SORASTBase **_root);
	void for_statement(SORASTBase **_root,  bool interp  );
	void for_iteration(SORASTBase **_root,  bool interp  );
	void generate_statement(SORASTBase **_root,  bool interp  );
	void if_statement(SORASTBase **_root,  bool interp  );
	void relate_statement(SORASTBase **_root,  bool interp  );
	void return_statement(SORASTBase **_root,  bool interp  );
	void select_statement(SORASTBase **_root,  bool interp  );
	void synch_service_statement(SORASTBase **_root,  bool interp  );
	void transform_statement(SORASTBase **_root,  bool interp  );
	void unrelate_statement(SORASTBase **_root,  bool interp  );
	void while_statement(SORASTBase **_root,  bool interp  );
	void while_iteration(SORASTBase **_root,  bool interp  );
	  I_SM_Evt_Inst*    event_spec(SORASTBase **_root, bool interp );
	  I_object_inst_ref_set_var*    instance_chain(SORASTBase **_root,  bool interp  );
	void object_spec(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  );
	void select_nowhere(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  );
	void select_where(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  );
	void select_from(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  );
	void expr(SORASTBase **_root,  GS_var_si &rvalue, bool interp  );
	void sub_expr(SORASTBase **_root,  GS_var_si &rvalue, bool interp  );
	void op_and(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void op_or(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void op_relational(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void op_addition(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void op_boolean_negation(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void op_multiplication(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void term(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void rval(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void constant_value(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void attribute_access(SORASTBase **_root,  bool p_is_rval, GS_var_si &p_rvalue, vchar*& lvalue_str, bool interp  );
	void param_data_access(SORASTBase **_root,  bool p_is_rval, GS_var_si &p_rvalue, vchar*& lvalue_str, bool interp  );
	void event_data_access(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void enumerator_literal(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void synch_service_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void transformer_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	void bridge_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  );
	
	public:
	SIM_SOR( P *p_p, GS_var_si& p_return_value, const Description& descrip ):
	p(p_p),
	st(p_p->st),
	pck(p_p->pck),
	er(p_p->er),
	trace(FALSE),
	dumpflag(FALSE),
	C_return_value(p_return_value),
	C_continue(FALSE),
	C_break(FALSE),
	C_return(FALSE),
	C_descrip(descrip)
	{}

	~SIM_SOR()
	{}

	void init( bool p_instance_sm, I_Object_Instance* p_orig_inst );

	void log_stmt ( SORAST* stmt );
	void log_expr ( SORAST* stmt, GS_var_si & p_expr_val );

	void interpret_create_event_statement( const vchar *p_var_name,  
	I_SM_Evt_Inst* p_einst_ptr ); 
	void interpret_create_object_statement( const vchar *lvalue, const vchar *obj_kl ); 
	void interpret_delete_statement( const vchar *p_rvalue ); 

	bool interpret_for_initial( const vchar *irv, const vchar *irsv, int lineNo );
	bool interpret_for_next();
	void interpret_for_exit();

	void interpret_generate_evt_statement( I_SM_Evt_Inst* p_einst_ptr ); 
	void interpret_generate_evt_inst_statement_var( const vchar *evt_var ); 
	void interpret_generate_evt_inst_statement_attr( const vchar *lvalue_str, 
	GS_var_si& event_inst_var_si); 
	void interpret_generate_evt_inst_statement( const vchar *p_event_var_str,
	I_event_inst_var* event_inst_var_ptr,
	I_SM_Evt_Inst* einst_ptr ); 

	void interpret_if_begin ();
	void interpret_if_end ();

	void interpret_relate_statement( const vchar *p_inst1_name, 
	const vchar *p_inst2_name, 
	const vchar *p_assoc_name, const vchar *p_rel, const vchar *p_phrase ); 

	void interpret_select_any_from_statement( const vchar * obj_kl, 
	const vchar *irv, SORAST* wc );
	void interpret_select_many_from_statement( const vchar * obj_kl, 
	const vchar *irv, SORAST* wc );
	void interpret_select_any_related_statement( const vchar *irv,
	I_object_inst_ref_set_var* inst_set,
	bool any_flag, SORAST* wc );
	void interpret_select_many_related_statement( const vchar *irv,
	I_object_inst_ref_set_var* inst_set,
	SORAST* wc );


	void interpret_unrelate_statement( const vchar *p_inst1_name, 
	const vchar *p_inst2_name, 
	const vchar *p_assoc_name, const vchar *p_rel, const vchar *p_phrase ); 

	void interpret_while_initial( int lineNo );
	void interpret_while_next();
	void interpret_while_exit();


	I_Object_Instance* interpret_event_spec_inst_ref ( const vchar * var_name );
	I_Object_Instance* interpret_event_spec_assigner ( const vchar * obj_kl );
	Object* interpret_event_spec_creator ( const vchar * obj_kl );
	void interpret_supp_data ( I_SM_Evt_Inst* einst_ptr, const vchar *supp_data_name, GS_var_si& data_val );

	void set_rel_phrases
	(I_Related_Object_Instance_Pair* p_roip_ptr, Relationship* p_ooa_rel_ptr);

	void interpret_op_relational_eq ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_relational_ne ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_relational_lt ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_relational_le ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_relational_gt ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_relational_ge ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_addition_plus ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_addition_minus ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_multiplication_times ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_multiplication_div ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );
	void interpret_op_multiplication_mod ( GS_var_si &p_rvalue, 
	GS_var_si &operand1, GS_var_si &operand2 );

	void interpret_op_cardinality ( GS_var_si &p_rvalue, 
	const vchar *local_var );
	void interpret_op_empty ( GS_var_si &p_rvalue, 
	const vchar *local_var );
	void interpret_op_not_empty ( GS_var_si &p_rvalue, 
	const vchar *local_var );
	
  void interpret_attribute_access ( bool is_rval, GS_var_si &p_rvalue, 
	const vchar *irv, const vchar *p_attr_name, vchar *& lvalue_str );

	void interpret_param_data_access ( bool is_rval, GS_var_si &p_rvalue, 
	const vchar *p_supp_data, vchar *& lvalue_str );
	void interpret_event_data_access ( GS_var_si &p_rvalue, 
	const vchar *p_supp_data );
	void interpret_enumerator_literal ( GS_var_si &p_rvalue, 
	const vchar *p_enum_data_type, const vchar *enumerator );
	void interpret_bridge_expr( const vchar *eekl, const vchar *func, 
	int num_params, Description param_names[], GS_var_si param_values[],
	bool param_readonly[], GS_var_si &p_rvalue ); 
	void interpret_bridge_descrip( const vchar *eekl, const vchar *func, 
	int num_params, Description param_names[], GS_var_si param_values[],
	bool param_readonly[], GS_var_si &p_rvalue ); 
	void interpret_transform_expr(const vchar *kl, const vchar *func, 
	int num_params, Description param_names[], GS_var_si param_values[],
	bool param_readonly[], GS_var_si &p_rvalue ); 
	void interpret_ib_transform_expr(const vchar *irv, const vchar *func, 
	int num_params, Description param_names[], GS_var_si param_values[],
	bool param_readonly[], GS_var_si &p_rvalue ); 
	static void interpret_synch_service_descrip( const vchar *func, 
	int num_params, Description param_names[], GS_var_si param_values[],
	bool param_readonly[], GS_var_si &p_rvalue ); 

	bool interpret_bridge_param ( const vchar *p_din, 
	Description& p_param_name,  GS_var_si &param_value );
	bool interpret_transform_param ( const vchar *p_din, 
	Description& p_param_name,  GS_var_si &param_value );
	bool interpret_synch_service_param ( const vchar *p_din, 
	Description& p_param_name,  GS_var_si &param_value );

	void interpret_where_clause( I_object_inst_ref_set_var* p_inst_set_var_ptr,
	SORAST* p_wc, bool p_any_flag );
	I_object_inst_ref_set_var* create__from_instances_of__no_push( const vchar * p_obj_kl, 
	SORAST* p_wc, bool p_any_flag );

	I_object_inst_ref_set_var* interpret_chain_start ( const vchar *p_irv );
	I_object_inst_ref_set_var* interpret_single_link ( const vchar *p_obj_kl,
	const vchar *p_rel, const vchar *p_rel_direction_str,
	I_object_inst_ref_set_var* p_start_inst_set_var_ptr );

	

	// need to break these into two action blocks, 
	// otherwise it's too big for Sorcerer

	void interpret__time__current_date (GS_var_si& p_rvalue_var_si);
	void interpret__time__create_date
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_second
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_minute
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_hour
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_day
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_month
	(int num_params,  Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__get_year
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__current_clock (GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_start
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_start_recurring
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_remaining_time
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_reset_time
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_add_time
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__time__timer_cancel
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__get_env_var
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__put_env_var ( int num_params, Description p_param_name[], GS_var_si p_param_value[]);
	void interpret__mc_dbms__shell_command
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__file_read
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__file_write
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__string_to_integer
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__string_to_real
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__integer_to_string
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__real_to_string
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);
	void interpret__mc_dbms__boolean_to_string
	( int num_params, Description p_param_name[], GS_var_si p_param_value[], GS_var_si& p_rvalue_var_si);

	void panic ( char *msg )
	{ throw msg; }

	void mismatched_range(int looking_for, int upper_token, SORASTBase *found);
	void missing_wildcard();
	void mismatched_token(int looking_for, SORASTBase *found);
	void no_viable_alt(char *rulename, SORASTBase *root);

	int get_inst_var_ptr( const vchar *p_inst_name,  
	I_Object_Instance*& p_oinst_ptr, Id& p_obj_id );
	int get_relationship_ptr( const vchar *p_rel_num,  
	Relationship*& p_ooa_rel_ptr, Id& p_rel_id );
	int correlate_object_instances ( Relationship* ooa_rel_ptr, 
	const Id& obj1_id, const Id& obj2_id, const Id& assoc_obj_id,
	const vchar *p_phrase,
	Id& oir1_id,
	t_boolean& is_oir1_many,
	Id& oir2_id,
	t_boolean& is_oir2_many,
	Id& assoc_oir_id,
	t_boolean& is_assoc_oir_many,
	int& p_formalizer );

	void do_relate_statement (
	const vchar *p_inst1_name, 
	const vchar *p_inst2_name, 
	const vchar *p_assoc_name, 
	I_Object_Instance* oinst1_ptr,
	const Id& obj1_id,
	I_Object_Instance* oinst2_ptr,
	const Id& obj2_id,
	I_Object_Instance* assoc_oinst_ptr,
	const Id& assoc_obj_id,
	Relationship* ooa_rel_ptr,
	Relationship* previous_ooa_rel_ptr,
	const vchar* p_rel,
	const vchar* p_phrase );

	void do_unrelate_statement (I_Object_Instance* oinst1_ptr,
	const Id& obj1_id,
	I_Object_Instance* oinst2_ptr,
	const Id& obj2_id,
	I_Object_Instance* assoc_oinst_ptr,
	const Id& assoc_obj_id,
	Relationship* ooa_rel_ptr,
	Relationship* previous_ooa_rel_ptr,
	const vchar* p_phrase );

	void find_other_relationships_formalized ( I_Object* p_obj_ptr, Relationship* p_ooa_rel_ptr,
	mc_dbms_Set<Referential_attribute*>& p_ref_attr_coll );

	I_Object_Instance* find_related_instance( 
	I_Object_Instance* oinst_ptr, Relationship* ooa_rel_ptr, 
	Description& phrase_str );

	protected:
	P *p;                  // parser
	BPSymbol_Table *st;    // initialized by al.g
	P_check *pck;          // initialized by al.g
	P_error *er;           // initialized by al.g
	bool trace;
	bool dumpflag;
	bool C_instance_sm;
	I_Object_Instance* C_orig_inst_ptr;
	GS_var_si& C_return_value;
	bool C_continue;
	bool C_break;
	bool C_return;
	const Description& C_descrip;

};

#endif /* SIM_SOR_h */

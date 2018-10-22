/*========================================================================
 *
 * File:      $RCSfile: P.h,v $
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
/*
 * P: P a r s e r  H e a d e r 
 *
 * Generated from: al.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-1999
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR20
 */

#ifndef P_h
#define P_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13320
#endif

class ASTBase;
#include "AParser.h"


#include "p_types.hh"
#include "myAST.h"
#include "p_symtbl.hh"
#include "p_msgs.hh"
#include "p_error.hh"
#include "p_check.hh"
#include "p_ckbase.hh"
#include "p_tthred.hh"
#include "d_typdef.hh"
#include "u_desc.hh"
#include <stdio.h>
class P : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
protected:
	static  const ANTLRChar *_token_tbl[];
private:

public:
void init( P_error *p_er,
P_checkBase *p_ck,
persObjPtr p_self,
persObjPtr p_rcvd_evt,
persObjPtr p_selected,
persObjPtr p_param ); 

  // this function is here purely to eliminate a compiler warning:
//    warning:  P::init()  hides virtual ANTLRParser::init() 
void init()
{ panic ( "incorrect parser initialization function called" ); }

  void setBufferAddr(const char *p_ascii_buffer,
const vchar *p_vchar_buffer);
void initReloc();
void initWSpec(bool p_trace, bool p_dump);
~P();
static const ANTLRChar *_get_token( const ANTLRTokenType token );
static const ANTLRChar * tokenName(ANTLRTokenType t);
void syn(ANTLRAbstractToken * tok,
ANTLRChar * egroup,
SetWordType * eset,
ANTLRTokenType etok,
int k);
bool enum_oper_check( AST* op );
bool accum_datatype( AST* e1, AST* e2, t_core_data_type &t1,
t_core_data_type t2,
bool &mismatch );
void tracein(const char *r);
void traceout(const char *r);

  void panic ( const char *msg )
{
	throw msg;
}

  // This is invoked externally
void parse_action(ASTBase **_root,int *_retsignal );

public:
P_error *er;
P_check *pck;
BPSymbol_Table *st;
P_treeThread *ttr;   // relocatables
P_treeThread *ttqm;  // question marks
bool relocflag;
bool wspecflag;
bool trace;
bool dumpflag;
bool sor;
bool severe_error;
// For parsing AL in bridge and transformer descriptions
bool return_valid;
bool return_found;
// For parsing AL in derived attributes
vchar* attribute_write_valid;
bool attribute_write_found;
// For insuring that selected is used in a where clause
bool selected_found;
bool in_where;
void* return_type_reqd;
// For handling param.a in AL specifications
enum al_spec_type
{
	AL_SPEC_NONE_E,
	AL_SPEC_STATE_ACTION_E,
	AL_SPEC_ASSIGNER_E,
	AL_SPEC_IB_ASSIGNER_E,
	AL_SPEC_BRIDGE_E,
	AL_SPEC_TRANSFORMER_E,
	AL_SPEC_IB_TRANSFORMER_E,
	AL_SPEC_SYNSVC_E,
	AL_SPEC_ATTRIBUTE_E
};
bool param_valid;
bool self_valid;
al_spec_type spec_type;
Description spec_descr;
int loop_clause_nest_level;
const char *ascii_buffer;
const vchar *orig_buffer;
protected:
	static SetWordType setwd1[179];
	static SetWordType setwd2[179];
	static SetWordType setwd3[179];
	static SetWordType setwd4[179];
	static SetWordType setwd5[179];
	static SetWordType setwd6[179];
	static SetWordType setwd7[179];
	static SetWordType setwd8[179];
	static SetWordType setwd9[179];
	static SetWordType err1[24];
	static SetWordType err2[24];
	static SetWordType err3[24];
	static SetWordType err4[24];
	static SetWordType setwd10[179];
	static SetWordType setwd11[179];
	static SetWordType TOK_COMPARISON_OPERATOR_set[24];
	static SetWordType TOK_PLUS_OR_MINUS_set[24];
	static SetWordType TOK_MULT_OP_set[24];
	static SetWordType setwd12[179];
	static SetWordType setwd13[179];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:

struct _rv40 {
	t_core_data_type t;
	ANTLRTokenType OorEE ;
};
	P(ANTLRTokenBuffer *input);
	void statement(ASTBase **_root,int *_retsignal);
	void al_spec(ASTBase **_root,int *_retsignal, al_spec_type p_type, char *p_descr, void* p_return_type_reqd, const vchar* p_attribute_write_valid );
	void valid_statement(ASTBase **_root,int *_retsignal);
	void if_clause_statement(ASTBase **_root,int *_retsignal);
	void for_clause_statement(ASTBase **_root,int *_retsignal);
	void while_clause_statement(ASTBase **_root,int *_retsignal);
	void unmatched_statement(ASTBase **_root,int *_retsignal);
	void assignment_statement(ASTBase **_root,int *_retsignal);
	void break_statement(ASTBase **_root,int *_retsignal);
	void bridge_statement(ASTBase **_root,int *_retsignal);
	void control_statement(ASTBase **_root,int *_retsignal);
	void continue_statement(ASTBase **_root,int *_retsignal);
	void create_event_statement(ASTBase **_root,int *_retsignal);
	void create_object_statement(ASTBase **_root,int *_retsignal);
	void debug_statement(ASTBase **_root,int *_retsignal);
	void delete_statement(ASTBase **_root,int *_retsignal);
	void empty_statement(ASTBase **_root,int *_retsignal);
	void for_statement(ASTBase **_root,int *_retsignal);
	void generate_statement(ASTBase **_root,int *_retsignal);
	void if_statement(ASTBase **_root,int *_retsignal);
	void implicit_assignment_statement(ASTBase **_root,int *_retsignal);
	void implicit_bridge_or_transform_statement(ASTBase **_root,int *_retsignal);
	void implicit_ib_transform_statement(ASTBase **_root,int *_retsignal);
	void relate_statement(ASTBase **_root,int *_retsignal);
	void return_statement(ASTBase **_root,int *_retsignal);
	void select_statement(ASTBase **_root,int *_retsignal);
	void synch_svc_statement(ASTBase **_root,int *_retsignal);
	void transform_statement(ASTBase **_root,int *_retsignal);
	void unrelate_statement(ASTBase **_root,int *_retsignal);
	void while_statement(ASTBase **_root,int *_retsignal);
	void unmatched_else_statement(ASTBase **_root,int *_retsignal);
	void unmatched_elif_statement(ASTBase **_root,int *_retsignal);
	void unmatched_end_statement(ASTBase **_root,int *_retsignal);
	void unmatched_end_in_for_clause(ASTBase **_root,int *_retsignal);
	void unmatched_end_in_if_clause(ASTBase **_root,int *_retsignal);
	void unmatched_end_in_while_clause(ASTBase **_root,int *_retsignal);
	 t_core_data_type   assignment_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   attribute_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval );
	 t_core_data_type   bridge_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue );
	struct _rv40 bridge_or_transform_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue );
	  t_core_data_type    bridge_expr(ASTBase **_root,int *_retsignal);
	  t_core_data_type    bridge_or_transform_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   enumerator_access(ASTBase **_root,int *_retsignal);
	void debug_operand(ASTBase **_root,int *_retsignal);
	 t_core_data_type   event_data_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval );
	void event_spec(ASTBase **_root,int *_retsignal);
	void function_parameters(ASTBase **_root,int *_retsignal);
	void inst_ref_var_or_ee_keyletters(ASTBase **_root,int *_retsignal);
	void instance_chain(ASTBase **_root,int *_retsignal, Obj_Card_e card );
	 persObjPtr   object_spec(ASTBase **_root,int *_retsignal, Obj_Card_e card );
	 t_core_data_type   param_data_access(ASTBase **_root,int *_retsignal, Assign_Val_e isLval );
	void supp_data(ASTBase **_root,int *_retsignal);
	 t_core_data_type   synch_svc_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue );
	 t_core_data_type   transform_ib_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue );
	  t_core_data_type    transform_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   transform_invocation(ASTBase **_root,int *_retsignal, bool requiresReturnValue );
	void where_spec(ASTBase **_root,int *_retsignal);
	void assoc_obj_inst_ref_var(ASTBase **_root,int *_retsignal);
	void attribute(ASTBase **_root,int *_retsignal);
	 t_core_data_type   bridge_function(ASTBase **_root,int *_retsignal, AST *ee_kl );
	void data_item(ASTBase **_root,int *_retsignal);
	void data_item_name(ASTBase **_root,int *_retsignal);
	void enum_data_type(ASTBase **_root,int *_retsignal);
	void enumerator(ASTBase **_root,int *_retsignal);
	void keyletters(ASTBase **_root,int *_retsignal);
	void ee_keyletters(ASTBase **_root,int *_retsignal);
	void event_label(ASTBase **_root,int *_retsignal);
	void event_meaning(ASTBase **_root,int *_retsignal);
	void general_name(ASTBase **_root,int *_retsignal);
	void svc_general_name(ASTBase **_root,int *_retsignal);
	void limited_name(ASTBase **_root,int *_retsignal);
	void inst_ref_set_var(ASTBase **_root,int *_retsignal);
	void inst_ref_var(ASTBase **_root,int *_retsignal);
	void kw_as_id1(ASTBase **_root,int *_retsignal);
	void kw_as_id2(ASTBase **_root,int *_retsignal);
	void kw_as_id3(ASTBase **_root,int *_retsignal);
	void kw_as_id4(ASTBase **_root,int *_retsignal);
	void local_variable(ASTBase **_root,int *_retsignal, Assign_Val_e isLval );
	void function_name(ASTBase **_root,int *_retsignal);
	void svc_function_name(ASTBase **_root,int *_retsignal);
	void obj_or_ee_keyletters(ASTBase **_root,int *_retsignal);
	void object_keyletters(ASTBase **_root,int *_retsignal);
	void phrase(ASTBase **_root,int *_retsignal);
	void relationship(ASTBase **_root,int *_retsignal);
	void supp_data_item(ASTBase **_root,int *_retsignal);
	 t_core_data_type   synch_svc_function(ASTBase **_root,int *_retsignal);
	 t_core_data_type   transformer_function(ASTBase **_root,int *_retsignal, AST *obj_kl_or_inst_ref_var, bool isInstanceBased );
	 t_core_data_type   expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   sub_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   conjunction(ASTBase **_root,int *_retsignal);
	 t_core_data_type   relational_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   addition(ASTBase **_root,int *_retsignal);
	 t_core_data_type   multiplication(ASTBase **_root,int *_retsignal);
	 t_core_data_type   sign_expr(ASTBase **_root,int *_retsignal);
	 t_core_data_type   boolean_negation(ASTBase **_root,int *_retsignal);
	 t_core_data_type   term(ASTBase **_root,int *_retsignal);
	  t_core_data_type    rval(ASTBase **_root,int *_retsignal);
	  t_core_data_type    variable(ASTBase **_root,int *_retsignal);
	 t_core_data_type   constant_value(ASTBase **_root,int *_retsignal);
	void quoted_string(ASTBase **_root,int *_retsignal);
	static SetWordType TOK_RESYNCH_set[24];
};

#endif /* P_h */

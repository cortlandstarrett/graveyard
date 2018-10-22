/*========================================================================
 *
 * File:      $RCSfile: sim.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:20 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/*
 * S O R C E R E R  T r a n s l a t i o n  H e a d e r
 *
 * SORCERER Developed by Terence Parr, Aaron Sawdey, & Gary Funck
 * Parr Research Corporation, Intrepid Technology, University of Minnesota
 * 1992-1994
 * SORCERER Version 100B25
 */
#define SORCERER_VERSION	10025
#define SORCERER_NONTRANSFORM
#include "STreeParser.h"
#include "SIM_SOR.h"

#include "p_types.hh"
#include "myAST.h"
#include "SIM_SOR.h"

#include "d_object.hh"
#include "d_nlevt.hh"
#include "d_pevt.hh"

#include "i_clock.hh"
#include "i_einst.hh"     // I_SM_Evt_Inst
#include "i_oinst.hh"

#include "gs_evt.hh"      // create__I_SM_Evt_Inst
#include "gs_sizes.hh"    // GS_MAX_NUM_CHAIN_LINKS
#include "gs_stack.hh"
#include "gs_sub.hh"
#include "gs_ui.hh"

#include "sw_index.hh"

#include "u_trace.hh"


void SIM_SOR::statement(SORASTBase **_root, bool tracex, bool dumpflagx )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_STATEMENTS) ) {
		trace = tracex;
		dumpflag = dumpflagx;
		_MATCH(TOK_STATEMENTS);
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				valid_statement(&_t,   !C_return  );
			}
			else {
			if ( _t!=NULL && (_t->type()==Eof) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("statement", _t);
			}
			}
		}
		}
		_MATCH(Eof);
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::valid_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN) ) {
		assignment_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_BRIDGE) ) {
		bridge_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTROL) ) {
		control_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_OBJECT) ) {
		create_object_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_DELETE) ) {
		delete_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_EMPTY) ) {
		empty_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SYNCH_SVC) ) {
		synch_service_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_TRANSFORM) ) {
		transform_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_EVENT) ) {
		create_event_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_GENERATE) ) {
		generate_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_RELATE) ) {
		relate_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||
	_t->type()==TOK_STMT_SELECT_MANY) ) {
		select_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_UNRELATE) ) {
		unrelate_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_IF) ) {
		if_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_BREAK) ) {
		break_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTINUE) ) {
		continue_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_FOR) ) {
		for_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_RETURN) ) {
		return_statement(&_t,   interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_WHILE) ) {
		while_statement(&_t,   interp  );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("valid_statement", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void SIM_SOR::assignment_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *lv=NULL;
	SORAST *aa=NULL;
	SORAST *pda=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN) ) {
		
		GS_var_si rvalue_si; 
		vchar *lvalue_str;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_ASSIGN);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp ) 
		{       
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__assign();
		}
		if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR) ) {
			_MATCH(TOK_LOCAL_VAR);
			lv=(SORAST *)_t;
			_RIGHT;
			expr(&_t,   rvalue_si, interp  );
			if (interp) GS_stack::place_result_in_stack_var (lv->getVcharText(), &rvalue_si);   
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			aa=(SORAST *)_t; attribute_access(&_t,   FALSE, rvalue_si, lvalue_str, interp  );
			expr(&_t,   rvalue_si, interp  );
			
			if (interp)
			{
				GS_stack::place_result_in_stack_var (lvalue_str, &rvalue_si); 
				delete [] lvalue_str;
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_PARAM||_t->type()==TOK_BRIDGE_PARAM||
		_t->type()==TOK_SYNCH_SVC_PARAM) ) {
			pda=(SORAST *)_t; param_data_access(&_t,   FALSE, rvalue_si, lvalue_str, interp  );
			expr(&_t,   rvalue_si, interp  );
			
			if (interp)
			{
				GS_stack::place_result_in_stack_var (lvalue_str, &rvalue_si); 
				delete [] lvalue_str;
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("assignment_statement", _t);
		}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("assignment_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::break_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_BREAK) ) {
		_MATCH(TOK_STMT_BREAK);
		stmt=(SORAST *)_t;
		_RIGHT;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__break();
			C_break = TRUE;
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("break_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::bridge_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_BRIDGE) ) {
		
		GS_var_si rvalue_si; 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_BRIDGE);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__bridge();
		}
		bridge_expr(&_t,   rvalue_si, interp  );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("bridge_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::control_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTROL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CONTROL);
		stmt=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_STOP);
		_RIGHT;
		
		if ( interp )
		{
			log_stmt ( stmt );
			W_index_window::stop_system_clock_tick();
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("control_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::continue_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTINUE) ) {
		_MATCH(TOK_STMT_CONTINUE);
		stmt=(SORAST *)_t;
		_RIGHT;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__continue();
			C_continue = TRUE;
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("continue_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::create_event_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *erv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_EVENT) ) {
		
		I_SM_Evt_Inst* einst_ptr = 0;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CREATE_EVENT);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__create_event_instance ();
		}
		_MATCH(TOK_EVENT_REF_VAR);
		erv=(SORAST *)_t;
		_RIGHT;
		  einst_ptr  =event_spec(&_t,   interp  );
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			if (einst_ptr)
			{
				interpret_create_event_statement( erv->getVcharText(), einst_ptr ); 
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("create_event_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::create_object_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *kl=NULL;
	SORAST *irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_OBJECT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CREATE_OBJECT);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__create_object_instance ();
		}
		_MATCH(TOK_KL_OBJECT);
		kl=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("create_object_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			if ( irv )
			interpret_create_object_statement( irv->getVcharText(), kl->getVcharText() ); 
			else
			interpret_create_object_statement( vcharGetEmptyString(), kl->getVcharText() ); 
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("create_object_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::delete_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_DELETE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_DELETE);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__delete_object_instance ();
		}
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		if (interp) interpret_delete_statement( irv->getVcharText() );   
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("delete_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::empty_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_STMT_EMPTY) ) {
		_MATCH(TOK_STMT_EMPTY);
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("empty_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::for_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *tsf=NULL;
	SORAST *irv=NULL;
	SORAST *irsv=NULL;
	SORAST *iter=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_FOR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_FOR);
		tsf=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_SET_VAR);
		irsv=(SORAST *)_t;
		_RIGHT;
		iter=(SORAST *)_t; for_iteration(&_t,   FALSE  );
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			log_stmt ( tsf );
			bool more_inst  = interpret_for_initial ( 
			irv->getVcharText(), irsv->getVcharText(), tsf->getLine() );
			while ( more_inst )
			{
				C_continue = FALSE;
				C_break = FALSE;
				SORASTBase *iter_root = iter;
				for_iteration ( &iter_root, TRUE );
				if ( C_break || C_return )
				{
					interpret_for_exit();
					// set break to FALSE to prevent an enclosing
					// for statement from also exiting
					C_break = FALSE;
					break;
				}
				more_inst  = interpret_for_next (); 
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("for_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::for_iteration(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_CLAUSE_FOR) ) {
		bool for_condition = interp;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_FOR);
		_DOWN;
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				valid_statement(&_t,   for_condition && !C_break && !C_continue && !C_return  );
				
				if ( for_condition && (C_break || C_continue || C_return) )
				for_condition = FALSE;
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("for_iteration", _t);
			}
			}
		}
		}
		_MATCH(TOK_CONTEXT_POP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("for_iteration", _t);
	}
	*_root = _t;
}

void SIM_SOR::generate_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *es=NULL;
	SORAST *erv=NULL;
	SORAST *aa=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_GENERATE) ) {
		
		I_SM_Evt_Inst* einst_ptr = 0;
		GS_var_si rvalue_si; 
		vchar *lvalue_str;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_GENERATE);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__generate ();
		}
		if ( _t!=NULL && (_t->type()==TOK_EVENT_LABEL) ) {
			es=(SORAST *)_t;   einst_ptr  =event_spec(&_t,   interp  );
			if (interp) 
			{
				if (einst_ptr)
				{
					interpret_generate_evt_statement( einst_ptr );
				}
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_EVENT_REF_VAR) ) {
			_MATCH(TOK_EVENT_REF_VAR);
			erv=(SORAST *)_t;
			_RIGHT;
			if (interp) interpret_generate_evt_inst_statement_var( erv->getVcharText() );   
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			aa=(SORAST *)_t; attribute_access(&_t,   TRUE, rvalue_si, lvalue_str, interp  );
			if (interp) interpret_generate_evt_inst_statement_attr( lvalue_str, rvalue_si ); 
			delete [] lvalue_str;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("generate_statement", _t);
		}
		}
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("generate_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::if_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *if_stmt=NULL;
	SORAST *elif_stmt=NULL;
	SORAST *else_stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_IF) ) {
		GS_var_si cond_val;
		bool if_condition = FALSE;
		bool block_executed = FALSE;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_IF);
		if_stmt=(SORAST *)_t;
		_DOWN;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_IF);
		_DOWN;
		
		if (interp)
		{
			log_stmt ( if_stmt );
			I_Clock::add_exec_time__stmt__if ();
		}
		expr(&_t,   cond_val, interp  );
		
		if (interp)
		{
			if ( cond_val.get_boolean_var_ptr () )
			{
				if_condition = cond_val.get_boolean_var_ptr ()->get_value () != FALSE;
			}
			else
			{
				if_condition = FALSE;
				GS_ui::inform (UI_INFORM__ERROR, GS_string("if expression isn't of type boolean, using FALSE"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"if expression isn't of type boolean"));
			}
		}
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		if (interp && if_condition) interpret_if_begin();   
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				valid_statement(&_t,   interp && if_condition && !C_break && !C_continue && !C_return  );
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("if_statement", _t);
			}
			}
		}
		}
		_MATCH(TOK_CONTEXT_POP);
		_RIGHT;
		
		if (interp && if_condition)
		{
			interpret_if_end();
			block_executed = TRUE;
		}
		_RESTORE;
		}
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_CLAUSE_ELIF) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_CLAUSE_ELIF);
				elif_stmt=(SORAST *)_t;
				_DOWN;
				
				if ( interp && !block_executed )
				{  
					log_stmt ( elif_stmt );
					I_Clock::add_exec_time__stmt__elif ();
				}
				expr(&_t,   cond_val, interp && !block_executed  );
				
				if (interp && !block_executed)
				{
					if ( cond_val.get_boolean_var_ptr () )
					{
						if_condition = cond_val.get_boolean_var_ptr ()->get_value () != FALSE;
					}
					else
					{
						if_condition = FALSE;
						GS_ui::inform (UI_INFORM__ERROR, GS_string("elif expression isn't of type boolean, using FALSE"));
						LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
						"elif expression isn't of type boolean"));
					}
				}
				_MATCH(TOK_CONTEXT_PUSH);
				_RIGHT;
				if (interp && !block_executed && if_condition ) interpret_if_begin();   
				{int _done=0;
				while ( !_done ) {
					if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
					_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
					_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
					_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
					_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
					_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
					_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
					_t->type()==TOK_STMT_WHILE) ) {
						valid_statement(&_t,   interp && !block_executed && if_condition && !C_break && !C_continue && !C_return  );
					}
					else {
					if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
						_done = 1;
					}
					else {
						if ( guessing ) _GUESS_FAIL;
						no_viable_alt("if_statement", _t);
					}
					}
				}
				}
				_MATCH(TOK_CONTEXT_POP);
				_RIGHT;
				
				if (interp && !block_executed && if_condition)
				{
					interpret_if_end();
					block_executed = TRUE;
				}
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t==NULL || (_t->type()==TOK_CLAUSE_ELSE) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("if_statement", _t);
			}
			}
		}
		}
		if ( _t!=NULL && (_t->type()==TOK_CLAUSE_ELSE) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_CLAUSE_ELSE);
			else_stmt=(SORAST *)_t;
			_DOWN;
			
			if ( interp && !block_executed )
			{  
				log_stmt ( else_stmt );
			}
			_MATCH(TOK_CONTEXT_PUSH);
			_RIGHT;
			if (interp && !block_executed) interpret_if_begin();   
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
				_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
				_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
				_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
				_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
				_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
				_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
				_t->type()==TOK_STMT_WHILE) ) {
					valid_statement(&_t,   interp && !block_executed && !C_break && !C_continue && !C_return  );
				}
				else {
				if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
					_done = 1;
				}
				else {
					if ( guessing ) _GUESS_FAIL;
					no_viable_alt("if_statement", _t);
				}
				}
			}
			}
			_MATCH(TOK_CONTEXT_POP);
			_RIGHT;
			
			if (interp && !block_executed)
			{
				interpret_if_end();
				block_executed = TRUE;
			}
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("if_statement", _t);
		}
		}
		
		if ( interp )
		{
			GS_UI_INFORM (UI_INFORM__STMT, GS_string("END IF;"));
		}
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("if_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::relate_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *irv1=NULL;
	SORAST *irv2=NULL;
	SORAST *rel=NULL;
	SORAST *ph=NULL;
	SORAST *assoc_irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_RELATE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_RELATE);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if ( interp )
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__relate ();
		}
		_MATCH(TOK_INST_REF_VAR);
		irv1=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_VAR);
		irv2=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_RELID);
		rel=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_PHRASE) ) {
			_MATCH(TOK_PHRASE);
			ph=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t->type()==TOK_INST_REF_VAR) ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("relate_statement", _t);
		}
		}
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			assoc_irv=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("relate_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			if ( assoc_irv == 0 )
			{
				interpret_relate_statement( irv1->getVcharText(), irv2->getVcharText(),
				0, rel->getVcharText(), ph->getVcharText() );
			}
			else
			{
				interpret_relate_statement( irv1->getVcharText(), irv2->getVcharText(), 
				assoc_irv->getVcharText(), rel->getVcharText(), ph->getVcharText() );
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("relate_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::return_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_RETURN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_RETURN);
		stmt=(SORAST *)_t;
		_DOWN;
		if (interp)
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__return();
		}
		if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
			expr(&_t,   C_return_value, interp  );
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("return_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
		if (interp)
		{
			C_return = TRUE; 
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("return_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::select_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt1=NULL;
	SORAST *irv=NULL;
	SORAST *stmt2=NULL;
	SORAST *stmt3=NULL;
	SORAST *irsv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||
	_t->type()==TOK_STMT_SELECT_MANY) ) {
		if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ONE) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_STMT_SELECT_ONE);
			stmt1=(SORAST *)_t;
			_DOWN;
			
			if (interp)
			{
				log_stmt ( stmt1 );
			}
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
			object_spec(&_t,   TOK_STMT_SELECT_ONE, irv->getVcharText(), interp  );
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ANY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_STMT_SELECT_ANY);
			stmt2=(SORAST *)_t;
			_DOWN;
			
			if (interp)
			{
				log_stmt ( stmt2 );
			}
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
			object_spec(&_t,   TOK_STMT_SELECT_ANY, irv->getVcharText(), interp  );
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_MANY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_STMT_SELECT_MANY);
			stmt3=(SORAST *)_t;
			_DOWN;
			
			if (interp)
			{
				log_stmt ( stmt3 );
			}
			_MATCH(TOK_INST_REF_SET_VAR);
			irsv=(SORAST *)_t;
			_RIGHT;
			object_spec(&_t,   TOK_STMT_SELECT_MANY, irsv->getVcharText(), interp  );
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("select_statement", _t);
		}
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::synch_service_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_SYNCH_SVC) ) {
		
		GS_var_si rvalue_si; 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_SYNCH_SVC);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if (interp)
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__synch_service();
		}
		synch_service_expr(&_t,   rvalue_si, interp  );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("synch_service_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::transform_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_TRANSFORM) ) {
		
		GS_var_si rvalue_si; 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_TRANSFORM);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if (interp)
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__transformation();
		}
		transformer_expr(&_t,   rvalue_si, interp  );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("transform_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::unrelate_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	SORAST *irv1=NULL;
	SORAST *irv2=NULL;
	SORAST *rel=NULL;
	SORAST *ph=NULL;
	SORAST *assoc_irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_UNRELATE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_UNRELATE);
		stmt=(SORAST *)_t;
		_DOWN;
		
		if (interp)
		{
			log_stmt ( stmt );
			I_Clock::add_exec_time__stmt__unrelate();
		}
		_MATCH(TOK_INST_REF_VAR);
		irv1=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_VAR);
		irv2=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_RELID);
		rel=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_PHRASE) ) {
			_MATCH(TOK_PHRASE);
			ph=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t==NULL || (_t->type()==TOK_INST_REF_VAR) ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("unrelate_statement", _t);
		}
		}
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			assoc_irv=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("unrelate_statement", _t);
		}
		}
		_RESTORE;
		}
		_RIGHT;
		
		if (interp)
		{
			if ( assoc_irv == 0 )
			{
				interpret_unrelate_statement( irv1->getVcharText(), irv2->getVcharText(),
				0, rel->getVcharText(), ph->getVcharText() );
			}
			else
			{
				interpret_unrelate_statement( irv1->getVcharText(), irv2->getVcharText(), 
				assoc_irv->getVcharText(), rel->getVcharText(), ph->getVcharText() );
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("unrelate_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::while_statement(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *ws=NULL;
	SORAST *we=NULL;
	SORAST *iter=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_WHILE) ) {
		GS_var_si cond_val;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_WHILE);
		ws=(SORAST *)_t;
		_DOWN;
		we=(SORAST *)_t; expr(&_t,   cond_val, FALSE  );
		iter=(SORAST *)_t; while_iteration(&_t,   FALSE  );
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			log_stmt ( ws );

			SORASTBase *expr_root = we;
			expr ( &expr_root, cond_val, TRUE );
			bool while_condition;
			if ( cond_val.get_boolean_var_ptr () )
			{
				while_condition = cond_val.
				get_boolean_var_ptr ()->get_value () != FALSE;  
			}
			else
			{
				while_condition = FALSE;
				GS_ui::inform (UI_INFORM__ERROR, GS_string("while expression isn't of type boolean, using FALSE"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"while expression isn't of type boolean"));
			}

			if ( while_condition )
			{  
			interpret_while_initial( ws->getLine() );
		}

		while ( while_condition )
		{
		C_continue = FALSE;
		C_break = FALSE;

		SORASTBase *iter_root = iter;
		while_iteration ( &iter_root, TRUE );

		if ( C_break || C_return )
		{
		interpret_while_exit();
		// set break to FALSE to prevent an enclosing
		// iteration statement from also exiting
		C_break = FALSE;
		break;
	}

	interpret_while_next();

	log_stmt ( ws );

	expr_root = we;
	expr ( &expr_root, cond_val, TRUE );
	if ( cond_val.get_boolean_var_ptr () )
	{
	while_condition = cond_val.
	get_boolean_var_ptr ()->get_value () != FALSE;
}
else
{
while_condition = FALSE;
GS_ui::inform (UI_INFORM__ERROR, GS_string("while expression isn't of type boolean, using FALSE"));
LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
"while expression isn't of type boolean"));
}

if ( !while_condition )
{  
interpret_while_exit();
}
}
}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("while_statement", _t);
	}
	*_root = _t;
}

void SIM_SOR::while_iteration(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_CLAUSE_WHILE) ) {
		
		bool while_condition = interp;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_WHILE);
		_DOWN;
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTROL||_t->type()==TOK_STMT_CONTINUE||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				valid_statement(&_t,   while_condition && !C_break && !C_continue && !C_return  );
				
				if ( while_condition && (C_break || C_continue || C_return) )
				while_condition = FALSE;
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("while_iteration", _t);
			}
			}
		}
		}
		_MATCH(TOK_CONTEXT_POP);
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("while_iteration", _t);
	}
	*_root = _t;
}

  I_SM_Evt_Inst*    SIM_SOR::event_spec(SORASTBase **_root, bool interp )
{
	SORASTBase *_t = *_root;
	  I_SM_Evt_Inst* einst_ptr  ;
	SORAST *evt_lbl=NULL;
	SORAST *kla=NULL;
	SORAST *klc=NULL;
	SORAST *irv=NULL;
	SORAST *sdn=NULL;
	if ( _t!=NULL && (_t->type()==TOK_EVENT_LABEL) ) {
		
		bool to_ext_ent = FALSE;
		I_Object_Instance* dest_oinst_ptr = 0;
		Object* ooa_obj_ptr = 0;
		einst_ptr = 0;
		if ( _t!=NULL && (_t->type()==TOK_EVENT_LABEL) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_EVENT_LABEL);
			evt_lbl=(SORAST *)_t;
			_DOWN;
			if ( _t!=NULL && (_t->type()==TOK_TIMES) ) {
				_MATCH(TOK_TIMES);
				_RIGHT;
			}
			else {
			if ( _t==NULL || (_t->type()==TOK_PHRASE) ) {
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("event_spec", _t);
			}
			}
			if ( _t!=NULL && (_t->type()==TOK_PHRASE) ) {
				_MATCH(TOK_PHRASE);
				_RIGHT;
			}
			else {
			if ( _t==NULL ) {
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("event_spec", _t);
			}
			}
			_RESTORE;
			}
			_RIGHT;
			if ( _t!=NULL && (_t->type()==TOK_KL_OBJECT_ASSIGNER) ) {
				_MATCH(TOK_KL_OBJECT_ASSIGNER);
				kla=(SORAST *)_t;
				_RIGHT;
				
				if ( interp )
				{
					dest_oinst_ptr = interpret_event_spec_assigner ( kla->getVcharText() );
				}
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_KL_OBJECT_CREATOR) ) {
				_MATCH(TOK_KL_OBJECT_CREATOR);
				klc=(SORAST *)_t;
				_RIGHT;
				
				if ( interp )
				{
					ooa_obj_ptr = interpret_event_spec_creator ( klc->getVcharText() );
				}
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
				_MATCH(TOK_INST_REF_VAR);
				irv=(SORAST *)_t;
				_RIGHT;
				
				if ( interp )
				{
					dest_oinst_ptr = interpret_event_spec_inst_ref ( irv->getVcharText() );
				}
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_KL_EXTERNAL_ENTITY) ) {
				_MATCH(TOK_KL_EXTERNAL_ENTITY);
				_RIGHT;
				to_ext_ent = TRUE;   
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("event_spec", _t);
			}
			}
			}
			}
			
			if ( interp )
			{
				if ( !to_ext_ent )
				{
					// HACK! - The validate routines should have found this pointer for us.
					D_sm_event* ooa_evt_ptr = (D_sm_event*) evt_lbl->getObjPtr();

					// Change non-local events to the polymorphic event they represent
					if ( ooa_evt_ptr->is_non_local_event() )
					{
						D_polymorphic_event* poly_evt_ptr = 
						ooa_evt_ptr->get_sem_event_ptr()->get_non_local_event_ptr()->get_aliased_polymorphic_event_ptr();
						if ( poly_evt_ptr )
						{
							ooa_evt_ptr = poly_evt_ptr;
						}
					}

					einst_ptr
					= GS_sim_evt::create__I_SM_Evt_Inst (ooa_evt_ptr->get_id ());

					if ( ooa_evt_ptr->is_polymorphic_event() )
					{
						einst_ptr->set_polymorphic_delivery(TRUE);
					}
					if (C_orig_inst_ptr)
					{
						C_orig_inst_ptr->relate_R2031 (einst_ptr);
					}

					if (dest_oinst_ptr)
					{
						dest_oinst_ptr->relate_R2032 (einst_ptr);
					}
					else
					{
						einst_ptr->is_creation_event() = TRUE;
						if ( ooa_obj_ptr )
						{
							einst_ptr->set_creation_Object_ID (ooa_obj_ptr->get_object_id());
						}
					}  
				}
			}
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_SUPP_DATA_NAME) ) {
					GS_var_si data_val;   
					{_SAVE; TREE_CONSTR_PTRS;
					_MATCH(TOK_SUPP_DATA_NAME);
					sdn=(SORAST *)_t;
					_DOWN;
					expr(&_t,   data_val, interp  );
					
					if (interp)
					{
						if ( !to_ext_ent )
						{
							interpret_supp_data ( einst_ptr, sdn->getVcharText(), data_val );
						}
					}
					_RESTORE;
					}
					_RIGHT;
				}
				else {
				if ( _t==NULL ) {
					_done = 1;
				}
				else {
					if ( guessing ) _GUESS_FAIL;
					no_viable_alt("event_spec", _t);
				}
				}
			}
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("event_spec", _t);
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("event_spec", _t);
	}
	*_root = _t;
	return einst_ptr;
}

  I_object_inst_ref_set_var*    SIM_SOR::instance_chain(SORASTBase **_root,  bool interp  )
{
	SORASTBase *_t = *_root;
	  I_object_inst_ref_set_var* result_set  ;
	SORAST *final_kl=NULL;
	SORAST *irv=NULL;
	SORAST *irsv=NULL;
	SORAST *kl=NULL;
	SORAST *rel=NULL;
	SORAST *ph=NULL;
	if ( _t!=NULL && (_t->type()==TOK_INST_REF) ) {
		
		int current_link_num = 0;    
		I_object_inst_ref_set_var* intermediate_set_ptr [GS_MAX_NUM_CHAIN_LINKS];
		if (interp)
		{
			for (t_uint i = 0; (i < GS_MAX_NUM_CHAIN_LINKS); i++)
			{
				intermediate_set_ptr [i] = 0;
			}
		}
		bool error_occurred = FALSE;
		_MATCH(TOK_INST_REF);
		final_kl=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
			
			if (interp)
			{
				intermediate_set_ptr[current_link_num] = interpret_chain_start ( irv->getVcharText() );
				if ( intermediate_set_ptr[current_link_num] == 0 )
				{
					error_occurred = TRUE;
				}
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_SET_VAR) ) {
			_MATCH(TOK_INST_REF_SET_VAR);
			irsv=(SORAST *)_t;
			_RIGHT;
			
			if (interp)
			{
				intermediate_set_ptr[current_link_num] = interpret_chain_start ( irsv->getVcharText() );
				if ( intermediate_set_ptr[current_link_num] == 0 )
				{
					error_occurred = TRUE;
				}
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("instance_chain", _t);
		}
		}
		{int _done=0;
		do {
			if ( _t!=NULL && (_t->type()==TOK_KL_OBJECT) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_KL_OBJECT);
				kl=(SORAST *)_t;
				_DOWN;
				_MATCH(TOK_RELID);
				rel=(SORAST *)_t;
				_RIGHT;
				if ( _t!=NULL && (_t->type()==TOK_PHRASE) ) {
					_MATCH(TOK_PHRASE);
					ph=(SORAST *)_t;
					_RIGHT;
				}
				else {
				if ( _t==NULL ) {
				}
				else {
					if ( guessing ) _GUESS_FAIL;
					no_viable_alt("instance_chain", _t);
				}
				}
				
				if (interp)
				{
					if ( ! error_occurred )
					{
						intermediate_set_ptr[current_link_num+1] = interpret_single_link ( kl->getVcharText(), 
						rel->getVcharText(), ph->getVcharText(),
						intermediate_set_ptr[current_link_num]
						);

						//  Get rid of the prior intermediate result.
						//
						delete intermediate_set_ptr [current_link_num];
						intermediate_set_ptr[current_link_num] = 0;
						
            if (intermediate_set_ptr [current_link_num+1] == 0)
						{
							//  Assume error message printed in interpret_single_link.
							//
							result_set = 0;
							error_occurred = TRUE;
						}
						current_link_num += 1;
					}
				}
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("instance_chain", _t);
			}
			}
		} while ( !_done );
		}
		
		if (interp)
		{
			if ( ! error_occurred )
			{
				result_set = intermediate_set_ptr[current_link_num];
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("instance_chain", _t);
	}
	*_root = _t;
	return result_set;
}

void SIM_SOR::object_spec(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_RELATED) ) {
		select_nowhere(&_t,   card, irv, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_RELATED_WHERE) ) {
		select_where(&_t,   card, irv, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_FROM) ) {
		select_from(&_t,   card, irv, interp  );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("object_spec", _t);
	}
	}
	}
	*_root = _t;
}

void SIM_SOR::select_nowhere(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_RELATED) ) {
		
		I_object_inst_ref_set_var* instance_set;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_RELATED);
		_DOWN;
		  instance_set  =instance_chain(&_t,   interp  );
		_RESTORE;
		}
		_RIGHT;
		
		if (interp)
		{
			I_Clock::add_exec_time__stmt__select_related_by ();
			if ( card == TOK_STMT_SELECT_ONE || card == TOK_STMT_SELECT_ANY )
			{
				interpret_select_any_related_statement( irv, instance_set, 
				card == TOK_STMT_SELECT_ANY, 0  );
			}
			else if ( card == TOK_STMT_SELECT_MANY )
			{
				interpret_select_many_related_statement( irv, instance_set, 0  );
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_nowhere", _t);
	}
	*_root = _t;
}

void SIM_SOR::select_where(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *wh=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RELATED_WHERE) ) {
		
		I_object_inst_ref_set_var* instance_set;
		GS_var_si where_val; 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_RELATED_WHERE);
		_DOWN;
		  instance_set  =instance_chain(&_t,   interp  );
		_RESTORE;
		}
		_RIGHT;
		_MATCH(TOK_WHERE);
		_RIGHT;
		wh=(SORAST *)_t; expr(&_t,   where_val, FALSE  );
		
		if (interp)
		{
			I_Clock::add_exec_time__stmt__select_related_by ();

			if ( card == TOK_STMT_SELECT_ONE || card == TOK_STMT_SELECT_ANY )
			{
				interpret_select_any_related_statement( irv, instance_set, 
				card == TOK_STMT_SELECT_ANY, wh );
			}
			else if ( card == TOK_STMT_SELECT_MANY )
			{
				interpret_select_many_related_statement( irv, instance_set, wh );
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_where", _t);
	}
	*_root = _t;
}

void SIM_SOR::select_from(SORASTBase **_root,   ANTLRTokenType card, const vchar *irv, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *kl=NULL;
	SORAST *wh=NULL;
	if ( _t!=NULL && (_t->type()==TOK_FROM) ) {
		
		GS_var_si where_val; 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_FROM);
		_DOWN;
		_MATCH(TOK_KL_OBJECT);
		kl=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_WHERE) ) {
			_MATCH(TOK_WHERE);
			_RIGHT;
			wh=(SORAST *)_t; expr(&_t,   where_val, FALSE  );
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("select_from", _t);
		}
		}
		
		if (interp)
		{
			I_Clock::add_exec_time__stmt__select_from_instances_of ();

			if ( card == TOK_STMT_SELECT_ANY )
			{
				interpret_select_any_from_statement( kl->getVcharText(), irv, wh  );
			}
			else if ( card == TOK_STMT_SELECT_MANY )
			{
				interpret_select_many_from_statement( kl->getVcharText(), irv, wh  );
			}
			else
			{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("Cardinality must be ANY or MANY in SELECT ... FROM INSTANCES OF"));
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_from", _t);
	}
	*_root = _t;
}

void SIM_SOR::expr(SORASTBase **_root,  GS_var_si &rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_EXPRESSION);
		_DOWN;
		sub_expr(&_t,   rvalue, interp  );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("expr", _t);
	}
	*_root = _t;
}

void SIM_SOR::sub_expr(SORASTBase **_root,  GS_var_si &rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
	_t->type()==TOK_TIMES||_t->type()==TOK_AND||_t->type()==TOK_OR||
	_t->type()==TOK_DOUBLEEQUAL||_t->type()==TOK_NOTEQUAL||_t->type()==TOK_LESSTHAN||
	_t->type()==TOK_LE||_t->type()==TOK_GT||_t->type()==TOK_GE||
	_t->type()==TOK_PLUS||_t->type()==TOK_MINUS||_t->type()==TOK_NOT||
	_t->type()==TOK_DIV||_t->type()==TOK_MOD||_t->type()==TOK_UNARY_PLUS||
	_t->type()==TOK_PAREN_EXPR||_t->type()==TOK_UNARY_MINUS||_t->type()==TOK_CARDINALITY||
	_t->type()==TOK_EMPTY||_t->type()==TOK_NOTEMPTY||_t->type()==TOK_FRACTION||
	_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||_t->type()==TOK_TRUETOKEN||
	_t->type()==TOK_FALSETOKEN||_t->type()==TOK_TRANSFORMER_PARAM||_t->type()==TOK_BRIDGE_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_RCVD_EVT||_t->type()==TOK_ENUMERATION||
	_t->type()==TOK_SYNCH_SVC_EXPR||_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR||
	_t->type()==TOK_BRIDGE_EXPR) ) {
		
		// This initialization must occur here, it has no other side effects.
		if ( interp ) rvalue.replace_var (new I_void_var ());
		if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
		_t->type()==TOK_UNARY_PLUS||_t->type()==TOK_PAREN_EXPR||_t->type()==TOK_UNARY_MINUS||
		_t->type()==TOK_CARDINALITY||_t->type()==TOK_EMPTY||_t->type()==TOK_NOTEMPTY||
		_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||
		_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN||_t->type()==TOK_TRANSFORMER_PARAM||
		_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_RCVD_EVT||
		_t->type()==TOK_ENUMERATION||_t->type()==TOK_SYNCH_SVC_EXPR||_t->type()==TOK_TRANSFORMER_EXPR||
		_t->type()==TOK_TRANSFORMER_IB_EXPR||_t->type()==TOK_BRIDGE_EXPR) ) {
			term(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_AND) ) {
			op_and(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_OR) ) {
			op_or(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_DOUBLEEQUAL||_t->type()==TOK_NOTEQUAL||
		_t->type()==TOK_LESSTHAN||_t->type()==TOK_LE||_t->type()==TOK_GT||
		_t->type()==TOK_GE) ) {
			op_relational(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_PLUS||_t->type()==TOK_MINUS) ) {
			op_addition(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_NOT) ) {
			op_boolean_negation(&_t,   rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_TIMES||_t->type()==TOK_DIV||
		_t->type()==TOK_MOD) ) {
			op_multiplication(&_t,   rvalue, interp  );
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("sub_expr", _t);
		}
		}
		}
		}
		}
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("sub_expr", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_and(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	if ( _t!=NULL && (_t->type()==TOK_AND) ) {
		
		GS_var_si operand1;
		GS_var_si operand2;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_AND);
		t_exp=(SORAST *)_t;
		_DOWN;
		sub_expr(&_t,   operand1, interp  );
		sub_expr(&_t,   operand2, interp  );
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			if ( operand1.get_boolean_var_ptr () ) 
			{
				if ( operand2.get_boolean_var_ptr () ) 
				{
					p_rvalue.replace_var (new I_boolean_var ((t_boolean)
					(operand1.get_boolean_var_ptr ()->get_value ()
					&& operand2.get_boolean_var_ptr ()->get_value ())));

					log_expr ( t_exp, p_rvalue );
					
          LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"BOOLEAN   AND   BOOLEAN"));
				}
				else
				{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("BOOLEAN  AND    ????"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"BOOLEAN AND    ????"));
				// HACK! - invalid expression
			}
		}
		else
		{
			if ( operand2.get_boolean_var_ptr () ) 
			{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("????  AND    BOOLEAN"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"????   AND    BOOLEAN"));
				// HACK! - invalid expression
			}
			else
			{
			GS_ui::inform (UI_INFORM__ERROR, GS_string("????  AND    ????"));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"????   AND    ????"));
			// HACK! - invalid expression
		}
	}
}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_and", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_or(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	if ( _t!=NULL && (_t->type()==TOK_OR) ) {
		
		GS_var_si operand1;
		GS_var_si operand2;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_OR);
		t_exp=(SORAST *)_t;
		_DOWN;
		sub_expr(&_t,   operand1, interp  );
		sub_expr(&_t,   operand2, interp  );
		_RESTORE;
		}
		_RIGHT;
		
		if ( interp )
		{
			if ( operand1.get_boolean_var_ptr () ) 
			{
				if ( operand2.get_boolean_var_ptr () ) 
				{
					p_rvalue.replace_var (new I_boolean_var ((t_boolean)
					(operand1.get_boolean_var_ptr ()->get_value ()
					|| operand2.get_boolean_var_ptr ()->get_value ())));

					log_expr ( t_exp, p_rvalue );

					LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"BOOLEAN   OR   BOOLEAN"));
				}
				else
				{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("BOOLEAN  OR    ????"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"BOOLEAN OR    ????"));
				// HACK! - invalid expression
			}
		}
		else
		{
			if ( operand2.get_boolean_var_ptr () ) 
			{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("????  OR    BOOLEAN"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"????   OR    BOOLEAN"));
				// HACK! - invalid expression
			}
			else
			{
			GS_ui::inform (UI_INFORM__ERROR, GS_string("????  OR    ????"));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"????   OR    ????"));
			// HACK! - invalid expression
		}
	}
}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_or", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_relational(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	SORAST *s3=NULL;
	SORAST *s4=NULL;
	SORAST *s5=NULL;
	SORAST *s6=NULL;
	SORAST *s7=NULL;
	SORAST *s8=NULL;
	SORAST *s9=NULL;
	SORAST *s10=NULL;
	SORAST *s11=NULL;
	SORAST *s12=NULL;
	if ( _t!=NULL && (_t->type()==TOK_DOUBLEEQUAL||_t->type()==TOK_NOTEQUAL||
	_t->type()==TOK_LESSTHAN||_t->type()==TOK_LE||_t->type()==TOK_GT||
	_t->type()==TOK_GE) ) {
		
		GS_var_si operand1;
		GS_var_si operand2;
		if ( _t!=NULL && (_t->type()==TOK_DOUBLEEQUAL) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_DOUBLEEQUAL);
			t_exp=(SORAST *)_t;
			_DOWN;
			s1=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s2=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_eq(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_NOTEQUAL) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_NOTEQUAL);
			t_exp=(SORAST *)_t;
			_DOWN;
			s3=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s4=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_ne(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_LESSTHAN) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_LESSTHAN);
			t_exp=(SORAST *)_t;
			_DOWN;
			s5=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s6=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_lt(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_LE) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_LE);
			t_exp=(SORAST *)_t;
			_DOWN;
			s7=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s8=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_le(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_GT) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_GT);
			t_exp=(SORAST *)_t;
			_DOWN;
			s9=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s10=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_gt(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_GE) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_GE);
			t_exp=(SORAST *)_t;
			_DOWN;
			s11=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s12=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_relational_ge(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("op_relational", _t);
		}
		}
		}
		}
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_relational", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_addition(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	SORAST *s3=NULL;
	SORAST *s4=NULL;
	if ( _t!=NULL && (_t->type()==TOK_PLUS||_t->type()==TOK_MINUS) ) {
		
		GS_var_si operand1;
		GS_var_si operand2;
		if ( _t!=NULL && (_t->type()==TOK_PLUS) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_PLUS);
			t_exp=(SORAST *)_t;
			_DOWN;
			s1=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s2=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_addition_plus(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_MINUS) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_MINUS);
			t_exp=(SORAST *)_t;
			_DOWN;
			s3=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s4=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_addition_minus(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("op_addition", _t);
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_addition", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_boolean_negation(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	if ( _t!=NULL && (_t->type()==TOK_NOT) ) {
		
		GS_var_si operand1;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_NOT);
		t_exp=(SORAST *)_t;
		_DOWN;
		sub_expr(&_t,   operand1, interp  );
		_RESTORE;
		}
		_RIGHT;
		
		if (interp)
		{
			if ( operand1.get_boolean_var_ptr () ) 
			{
				p_rvalue.replace_var (new I_boolean_var ((t_boolean)
				(!operand1.get_boolean_var_ptr ()->get_value ()) ));

				log_expr ( t_exp, p_rvalue );
				
        LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"NOT   BOOLEAN"));
			}
			else
			{
			GS_ui::inform (UI_INFORM__ERROR, GS_string("NOT   ????"));
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"NOT   ????"));
			// HACK! - invalid expression
		}
	}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_boolean_negation", _t);
	}
	*_root = _t;
}

void SIM_SOR::op_multiplication(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	SORAST *s3=NULL;
	SORAST *s4=NULL;
	SORAST *s5=NULL;
	SORAST *s6=NULL;
	if ( _t!=NULL && (_t->type()==TOK_TIMES||_t->type()==TOK_DIV||
	_t->type()==TOK_MOD) ) {
		
		GS_var_si operand1;
		GS_var_si operand2;
		if ( _t!=NULL && (_t->type()==TOK_TIMES) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_TIMES);
			t_exp=(SORAST *)_t;
			_DOWN;
			s1=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s2=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_multiplication_times(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_DIV) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_DIV);
			t_exp=(SORAST *)_t;
			_DOWN;
			s3=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s4=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_multiplication_div(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_MOD) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_MOD);
			t_exp=(SORAST *)_t;
			_DOWN;
			s5=(SORAST *)_t; sub_expr(&_t,   operand1, interp  );
			s6=(SORAST *)_t; sub_expr(&_t,   operand2, interp  );
			_RESTORE;
			}
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_multiplication_mod(p_rvalue, operand1, operand2);
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("op_multiplication", _t);
		}
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_multiplication", _t);
	}
	*_root = _t;
}

void SIM_SOR::term(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *t_exp=NULL;
	SORAST *t1=NULL;
	SORAST *lv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
	_t->type()==TOK_UNARY_PLUS||_t->type()==TOK_PAREN_EXPR||_t->type()==TOK_UNARY_MINUS||
	_t->type()==TOK_CARDINALITY||_t->type()==TOK_EMPTY||_t->type()==TOK_NOTEMPTY||
	_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||
	_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN||_t->type()==TOK_TRANSFORMER_PARAM||
	_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_RCVD_EVT||
	_t->type()==TOK_ENUMERATION||_t->type()==TOK_SYNCH_SVC_EXPR||_t->type()==TOK_TRANSFORMER_EXPR||
	_t->type()==TOK_TRANSFORMER_IB_EXPR||_t->type()==TOK_BRIDGE_EXPR) ) {
		
		GS_var_si operand1;
		if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
		_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||
		_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN||_t->type()==TOK_TRANSFORMER_PARAM||
		_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_RCVD_EVT||
		_t->type()==TOK_ENUMERATION||_t->type()==TOK_SYNCH_SVC_EXPR||_t->type()==TOK_TRANSFORMER_EXPR||
		_t->type()==TOK_TRANSFORMER_IB_EXPR||_t->type()==TOK_BRIDGE_EXPR) ) {
			rval(&_t,   p_rvalue, interp  );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_UNARY_PLUS) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_UNARY_PLUS);
			_DOWN;
			term(&_t,   p_rvalue, interp  );
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_PAREN_EXPR) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_PAREN_EXPR);
			_DOWN;
			expr(&_t,   p_rvalue, interp  );
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_UNARY_MINUS) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_UNARY_MINUS);
			t_exp=(SORAST *)_t;
			_DOWN;
			t1=(SORAST *)_t; term(&_t,   operand1, interp  );
			
			if ( interp )
			{
				if ( t1->getDatatype() == INTEGER_DATATYPE && 
				operand1.get_integer_var_ptr () ) 
				{
					p_rvalue.replace_var (new I_integer_var ((t_long)
					(- operand1.get_integer_var_ptr ()->get_value () )));
					log_expr ( t_exp, p_rvalue );
					LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
					"-   INTEGER"));
				}
				else if ( t1->getDatatype() == REAL_DATATYPE &&
				operand1.get_real_var_ptr () ) 
				{
				p_rvalue.replace_var (new I_real_var ((t_double)
				(- operand1.get_real_var_ptr ()->get_value () )));
				log_expr ( t_exp, p_rvalue );
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"-   REAL"));
			}
			else
			{
				GS_ui::inform (UI_INFORM__ERROR, GS_string("-   ????"));
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"-   ????"));
				// HACK! - invalid expression
			}
		}
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_CARDINALITY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_CARDINALITY);
			t_exp=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_LOCAL_VAR);
			lv=(SORAST *)_t;
			_RIGHT;
			
			if (interp) 
			{
				interpret_op_cardinality( p_rvalue, lv->getVcharText() );
				log_expr ( t_exp, p_rvalue );
			}
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_EMPTY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_EMPTY);
			t_exp=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_LOCAL_VAR);
			lv=(SORAST *)_t;
			_RIGHT;
			
			if (interp)
			{
				interpret_op_empty( p_rvalue, lv->getVcharText() );
				log_expr ( t_exp, p_rvalue );
			}
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_NOTEMPTY) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_NOTEMPTY);
			t_exp=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_LOCAL_VAR);
			lv=(SORAST *)_t;
			_RESTORE;
			}
			_RIGHT;
			
			if (interp)
			{
				interpret_op_not_empty( p_rvalue, lv->getVcharText() );
				log_expr ( t_exp, p_rvalue );
			}
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("term", _t);
		}
		}
		}
		}
		}
		}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("term", _t);
	}
	*_root = _t;
}

void SIM_SOR::rval(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *lv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||
	_t->type()==TOK_STRING||_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN) ) {
		constant_value(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_RCVD_EVT) ) {
		event_data_access(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_PARAM||_t->type()==TOK_BRIDGE_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM) ) {
		vchar *unused_lvalue = 0;    
		param_data_access(&_t,   TRUE, p_rvalue, unused_lvalue, interp  );
		delete [] unused_lvalue;   
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_ENUMERATION) ) {
		enumerator_literal(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_EXPR) ) {
		bridge_expr(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		synch_service_expr(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR) ) {
		transformer_expr(&_t,   p_rvalue, interp  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
		vchar *unused_lvalue = 0;   
		attribute_access(&_t,   TRUE, p_rvalue, unused_lvalue, interp  );
		delete [] unused_lvalue;   
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR) ) {
		_MATCH(TOK_LOCAL_VAR);
		lv=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			I_var* var_ptr = GS_stack::find_var_ptr (lv->getVcharText());
			if (! var_ptr)
			{
				Description err_msg ("Unable to find '");
				err_msg += lv->getVcharText();
				err_msg += "' on stack.";
				GS_ui::inform (UI_INFORM__ERROR, err_msg);
				LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
				"End:  SIM_SOR::rval (VOID_DATATYPE)."));
			}
			else
			{
			p_rvalue.replace_var (var_ptr);
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += lv->getVcharText();
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::rval ()."));
		}
	}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("rval", _t);
	}
	}
	}
	}
	}
	}
	}
	}
	}
	*_root = _t;
}

void SIM_SOR::constant_value(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *fr=NULL;
	SORAST *num=NULL;
	SORAST *str=NULL;
	SORAST *tt=NULL;
	SORAST *ft=NULL;
	if ( _t!=NULL && (_t->type()==TOK_FRACTION) ) {
		_MATCH(TOK_FRACTION);
		fr=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			t_double tmp_double = vnumParseFloat(fr->getVcharText(), 0);
			p_rvalue.replace_var (new I_real_var (tmp_double));
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += fr->getVcharText();
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::constant_value (REAL_DATATYPE)."));
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_NUMBER) ) {
		_MATCH(TOK_NUMBER);
		num=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			t_long tmp_long = vnumParseLong(num->getVcharText(), 0);
			p_rvalue.replace_var (new I_integer_var (tmp_long));
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += num->getVcharText();
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::constant_value (INTEGER_DATATYPE)."));
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STRING) ) {
		_MATCH(TOK_STRING);
		str=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			// need to add surrounding quotes back in for parse_token__quoted_str
			Description tmp_str1 ("\"");
			tmp_str1 += str->getVcharText();
			tmp_str1 += "\""; 
			t_uint tmp_str1_cursor = 0;
			Description tmp_str2;
			tmp_str1.parse_token__quoted_str (tmp_str1_cursor, tmp_str2);
			Description& tmp_str3 = GS_substitution::substitute_string
			(tmp_str2, FALSE);
			p_rvalue.replace_var (new I_string_var (tmp_str3));
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += tmp_str1;
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::constant_value (STRING_DATATYPE)."));
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRUETOKEN) ) {
		_MATCH(TOK_TRUETOKEN);
		tt=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			p_rvalue.replace_var (new I_boolean_var ((t_boolean) TRUE));
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += tt->getVcharText();
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::constant_value (BOOLEAN_DATATYPE = TRUE)."));
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_FALSETOKEN) ) {
		_MATCH(TOK_FALSETOKEN);
		ft=(SORAST *)_t;
		_RIGHT;
		
		if (interp)
		{
			p_rvalue.replace_var (new I_boolean_var ((t_boolean) FALSE));
			GS_UI_INFORM_START (UI_INFORM__COMP)
			Description err_msg ("rvalue '");
			err_msg += ft->getVcharText();
			err_msg += "' (";
			err_msg += p_rvalue.get_var_ptr ()->get_data_type_str ();
			err_msg += ") = ";
			err_msg += p_rvalue.get_var_ptr ()->get_value_str ();
			GS_UI_INFORM_END (UI_INFORM__COMP, err_msg)
			LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
			"End:  SIM_SOR::constant_value (BOOLEAN_DATATYPE = FALSE)."));
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("constant_value", _t);
	}
	}
	}
	}
	}
	*_root = _t;
}

void SIM_SOR::attribute_access(SORASTBase **_root,  bool p_is_rval, GS_var_si &p_rvalue, vchar*& lvalue_str, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *irv=NULL;
	SORAST *oa=NULL;
	if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_OBJ_ATTR);
		oa=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		if (interp)
		{
			interpret_attribute_access( p_is_rval, p_rvalue, 
			irv->getVcharText(), oa->getVcharText(), lvalue_str );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("attribute_access", _t);
	}
	*_root = _t;
}

void SIM_SOR::param_data_access(SORASTBase **_root,  bool p_is_rval, GS_var_si &p_rvalue, vchar*& lvalue_str, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *din=NULL;
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_PARAM||_t->type()==TOK_BRIDGE_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM) ) {
		if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_PARAM) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_TRANSFORMER_PARAM);
			_DOWN;
			_MATCH(TOK_DATA_ITEM_NAME);
			din=(SORAST *)_t;
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_BRIDGE_PARAM) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_BRIDGE_PARAM);
			_DOWN;
			_MATCH(TOK_DATA_ITEM_NAME);
			din=(SORAST *)_t;
			_RESTORE;
			}
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_PARAM) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_SYNCH_SVC_PARAM);
			_DOWN;
			_MATCH(TOK_DATA_ITEM_NAME);
			din=(SORAST *)_t;
			_RESTORE;
			}
			_RIGHT;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("param_data_access", _t);
		}
		}
		}
		
		if ( interp ) 
		{
			interpret_param_data_access ( p_is_rval, p_rvalue, 
			din->getVcharText(), lvalue_str );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("param_data_access", _t);
	}
	*_root = _t;
}

void SIM_SOR::event_data_access(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *sd=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RCVD_EVT) ) {
		_MATCH(TOK_RCVD_EVT);
		_RIGHT;
		_MATCH(TOK_SUPP_DATA_NAME);
		sd=(SORAST *)_t;
		_RIGHT;
		
		if ( interp ) interpret_event_data_access ( p_rvalue, sd->getVcharText() );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("event_data_access", _t);
	}
	*_root = _t;
}

void SIM_SOR::enumerator_literal(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *edt=NULL;
	SORAST *enum_value=NULL;
	if ( _t!=NULL && (_t->type()==TOK_ENUMERATION) ) {
		_MATCH(TOK_ENUMERATION);
		edt=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_ENUMERATOR);
		enum_value=(SORAST *)_t;
		_RIGHT;
		
		if ( interp ) 
		interpret_enumerator_literal ( p_rvalue, 
		edt->getVcharText(), enum_value->getVcharText() );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("enumerator_literal", _t);
	}
	*_root = _t;
}

void SIM_SOR::synch_service_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *sse=NULL;
	SORAST *func=NULL;
	SORAST *din=NULL;
	SORAST *pe=NULL;
	if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		
		Description param_name[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		GS_var_si param_val[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		bool param_readonly[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		int num_params = 0;
		bool param_ok = TRUE;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_SYNCH_SVC_EXPR);
		sse=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_FUNCTION_NAME);
		func=(SORAST *)_t;
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_DATA_ITEM_NAME);
				din=(SORAST *)_t;
				_DOWN;
				pe=(SORAST *)_t; expr(&_t,   param_val[num_params], interp  );
				
				if (param_ok && interp )
				{
					param_ok = interpret_synch_service_param ( din->getVcharText(), 
					param_name[num_params], param_val[num_params] );
					param_readonly[num_params] = pe->isReadOnly() != FALSE;
					num_params += 1; 
				}
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("synch_service_expr", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
		if (param_ok && interp)
		{
			interpret_synch_service_descrip( func->getVcharText(), 
			num_params, param_name, param_val, param_readonly, p_rvalue );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("synch_service_expr", _t);
	}
	*_root = _t;
}

void SIM_SOR::transformer_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *te=NULL;
	SORAST *kl=NULL;
	SORAST *func=NULL;
	SORAST *din=NULL;
	SORAST *pe=NULL;
	SORAST *s=NULL;
	SORAST *irv=NULL;
	SORAST *meth=NULL;
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR) ) {
		
		Description param_name[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		GS_var_si param_val[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		bool param_readonly[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		int num_params = 0;
		bool param_ok = TRUE;
		bool instance_based = FALSE;
		if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_TRANSFORMER_EXPR);
			te=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_KL_OBJECT);
			kl=(SORAST *)_t;
			_RIGHT;
			_MATCH(TOK_FUNCTION_NAME);
			func=(SORAST *)_t;
			_RIGHT;
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
					{_SAVE; TREE_CONSTR_PTRS;
					_MATCH(TOK_DATA_ITEM_NAME);
					din=(SORAST *)_t;
					_DOWN;
					pe=(SORAST *)_t; expr(&_t,   param_val[num_params], interp  );
					
					if (param_ok && interp )
					{
						param_ok = interpret_transform_param ( din->getVcharText(), 
						param_name[num_params], param_val[num_params] );
						param_readonly[num_params] = pe->isReadOnly() != FALSE;
						num_params += 1; 
					}
					_RESTORE;
					}
					_RIGHT;
				}
				else {
				if ( _t==NULL ) {
					_done = 1;
				}
				else {
					if ( guessing ) _GUESS_FAIL;
					no_viable_alt("transformer_expr", _t);
				}
				}
			}
			}
			_RESTORE;
			}
			_RIGHT;
			
			instance_based = FALSE;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_IB_EXPR) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_TRANSFORMER_IB_EXPR);
			s=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
			_MATCH(TOK_FUNCTION_NAME);
			meth=(SORAST *)_t;
			_RIGHT;
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
					{_SAVE; TREE_CONSTR_PTRS;
					_MATCH(TOK_DATA_ITEM_NAME);
					din=(SORAST *)_t;
					_DOWN;
					pe=(SORAST *)_t; expr(&_t,   param_val[num_params], interp  );
					
					if (param_ok && interp )
					{
						param_ok = interpret_transform_param ( din->getVcharText(), 
						param_name[num_params], param_val[num_params] );
						param_readonly[num_params] = pe->isReadOnly() != FALSE;
						num_params += 1; 
					}
					_RESTORE;
					}
					_RIGHT;
				}
				else {
				if ( _t==NULL ) {
					_done = 1;
				}
				else {
					if ( guessing ) _GUESS_FAIL;
					no_viable_alt("transformer_expr", _t);
				}
				}
			}
			}
			_RESTORE;
			}
			_RIGHT;
			
			instance_based = TRUE;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("transformer_expr", _t);
		}
		}
		if (param_ok && interp)
		{
			if ( instance_based )
			{
				interpret_ib_transform_expr( irv->getVcharText(), meth->getVcharText(), 
				num_params, param_name, param_val, param_readonly, p_rvalue );
			}
			else
			{
				interpret_transform_expr( kl->getVcharText(), func->getVcharText(), 
				num_params, param_name, param_val, param_readonly, p_rvalue );
			}
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("transformer_expr", _t);
	}
	*_root = _t;
}

void SIM_SOR::bridge_expr(SORASTBase **_root,  GS_var_si &p_rvalue, bool interp  )
{
	SORASTBase *_t = *_root;
	SORAST *eekl=NULL;
	SORAST *func=NULL;
	SORAST *din=NULL;
	SORAST *pe=NULL;
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_EXPR) ) {
		
		Description param_name[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		GS_var_si param_val[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		bool param_readonly[GS_MAX_NUM_PARAMS_PER_FUNC_DEF];
		int num_params = 0;
		bool param_ok = TRUE;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_BRIDGE_EXPR);
		_DOWN;
		_MATCH(TOK_KL_EXTERNAL_ENTITY);
		eekl=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_FUNCTION_NAME);
		func=(SORAST *)_t;
		_RIGHT;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_DATA_ITEM_NAME);
				din=(SORAST *)_t;
				_DOWN;
				pe=(SORAST *)_t; expr(&_t,   param_val[num_params], interp  );
				
				if ( param_ok && interp )
				{
					param_ok = interpret_bridge_param ( din->getVcharText(), 
					param_name[num_params], param_val[num_params] );
					param_readonly[num_params] = pe->isReadOnly() != FALSE;
					num_params += 1; 
				}
				_RESTORE;
				}
				_RIGHT;
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("bridge_expr", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
		if (param_ok && interp)
		{
			interpret_bridge_expr( eekl->getVcharText(), func->getVcharText(), 
			num_params, param_name, param_val, param_readonly, p_rvalue );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("bridge_expr", _t);
	}
	*_root = _t;
}

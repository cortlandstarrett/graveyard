/*========================================================================
 *
 * File:      $RCSfile: genal.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:22 $
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
#include "GEN_SOR.h"

#include "p_types.hh"
#include "p_swhere.hh"
#include "myAST.h"
#include "GEN_SOR.h"
#include "u_string.hh"
#include "u_desc.hh"

extern Special_Where* G_Special_Where_table;

void GEN_SOR::statement(SORASTBase **_root, bool tracex, bool dumpflagx, int actn_type )
{
	SORASTBase *_t = *_root;
	SORAST *vs=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STATEMENTS) ) {
		trace = tracex;
		dumpflag = dumpflagx;
		_MATCH(TOK_STATEMENTS);
		_RIGHT;
		
		script_var_name actn1;
		next_actn_var_name ( actn1 );
		switch ( actn_type )
		{
			case 0:
			*out_file << ".Invoke " << actn1 << " = actn_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			case 1:
			*out_file << ".Invoke " << actn1 << " = actn_bridge_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			case 2:
			*out_file << ".Invoke " << actn1 << " = actn_trans_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			case 3:
			*out_file << ".Invoke " << actn1 << " = actn_synch_service_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			case 4:
			*out_file << ".Invoke " << actn1 << " = actn_ib_trans_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			case 5:
			*out_file << ".Invoke " << actn1 << " = actn_attribute_begin (" 
			<< C_actn_var_name << ")" << endl;
			break;
			default:
			*out_file << ".print \"ERROR - unknown action specification type = " << actn_type << "\"";
			return;
		}

		new_scope();

		if ( C_instance_sm )
		{
			script_var_name var1;
			next_var_var_name ( var1 );
			*out_file << ".Invoke " << var1 << " = var_declare_self_obj_inst_ref ("
			<< C_actn_var_name << ")" << endl;
			vchar self_str[5];
			vcharCopyFromLiteral( "self", self_str );
			add_var_to_scope( self_str, C_obj_kl, var1 );
			vcharCopyFromLiteral( "Self", self_str );
			add_var_to_scope( self_str, C_obj_kl, var1 );
			vcharCopyFromLiteral( "SELF", self_str );
			add_var_to_scope( self_str, C_obj_kl, var1 );
			set_var_declared_in_scope( self_str );
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				vs=(SORAST *)_t; valid_statement(&_t);
				add_valid_statement( vs->getGenVarName() );   
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
		
		delete_all_var_from_scope();
		drop_scope();

		script_var_name actn2;
		next_actn_var_name ( actn2 );
		script_var_name last_blck;   
		get_previous_block ( last_blck ); 
		*out_file << ".Invoke " << actn2 << " = actn_append_blck (" 
		<< actn1 << ", " << last_blck << ")" << endl;

		script_var_name actn3;
		next_actn_var_name ( actn3 );
		*out_file << ".Invoke " << actn3 << " = actn_end (" << actn2 << ")" << endl;
		*out_file << "${" << actn3 << ".body}" << endl;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::valid_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN) ) {
		assignment_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_BREAK) ) {
		break_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_BRIDGE) ) {
		bridge_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTROL) ) {
		control_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTINUE) ) {
		continue_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_EVENT) ) {
		create_event_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_OBJECT) ) {
		create_object_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_DELETE) ) {
		delete_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_EMPTY) ) {
		empty_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_FOR) ) {
		for_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_GENERATE) ) {
		generate_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_IF) ) {
		if_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_RELATE) ) {
		relate_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_RETURN) ) {
		return_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||
	_t->type()==TOK_STMT_SELECT_MANY) ) {
		select_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SYNCH_SVC) ) {
		synch_svc_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_TRANSFORM) ) {
		transform_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_UNRELATE) ) {
		unrelate_statement(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_WHILE) ) {
		while_statement(&_t);
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

void GEN_SOR::assignment_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *lv=NULL;
	SORAST *e1=NULL;
	SORAST *aa=NULL;
	SORAST *e2=NULL;
	SORAST *pda=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_ASSIGN);
		a=(SORAST *)_t;
		_DOWN;
		if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR) ) {
			_MATCH(TOK_LOCAL_VAR);
			lv=(SORAST *)_t;
			_RIGHT;
			e1=(SORAST *)_t; expr(&_t);
			
			script_var_name gen_name;
			if ( is_var_in_scope(lv->getVcharText()) )
			{
				get_gen_name( lv->getVcharText(), gen_name );
				lv->setGenVarName( gen_name );
			}
			else
			{
				next_var_var_name ( gen_name );
				if ( lv->getDatatype() == OBJECT_INST_REF_DATATYPE )
				{
					vchar *obj_kl = C_last_resort_key_letters;
					declare_oir( gen_name, lv->getVcharText(), obj_kl);
					add_var_to_scope( lv->getVcharText(), obj_kl, gen_name );
				}
				else if ( lv->getDatatype() == OBJECT_INST_REF_SET_DATATYPE )
				{
					vchar *obj_kl = C_last_resort_key_letters;
					declare_oirs( gen_name, lv->getVcharText(), obj_kl);
					add_var_to_scope( lv->getVcharText(), obj_kl, gen_name );
				}
				else
				{
					*out_file << ".Invoke " << gen_name << " = var_declare (\""
					<< lv->getVcharText()  << "\")" << endl;
					add_var_to_scope( lv->getVcharText(), vcharGetEmptyString(), gen_name );
				}
				lv->setGenVarName( gen_name );
			}

			script_var_name var_name;
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_assign_transient_var (" << lv->getGenVarName();
			if ( is_var_declared_in_scope(lv->getVcharText()) )
			*out_file << ", FALSE, ";
			else
			*out_file << ", TRUE, ";
			*out_file << e1->getGenVarName() << ")" << endl;
			set_var_declared_in_scope(lv->getVcharText());
			a->setGenVarName( var_name );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			aa=(SORAST *)_t; attribute_access(&_t);
			e2=(SORAST *)_t; expr(&_t);
			
			script_var_name var_name;
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_assign_obj_attr (" << aa->getGenVarName()
			<< ", \"" << aa->child()->getVcharText() << "\", "
			<< e2->getGenVarName() << ")" << endl;
			a->setGenVarName( var_name );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_TRANSFORMER_PARAM||
		_t->type()==TOK_SYNCH_SVC_PARAM) ) {
			pda=(SORAST *)_t; param_data_access(&_t,   FALSE  );
			e2=(SORAST *)_t; expr(&_t);
			
			script_var_name var_name;
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name;
			if ( pda->getType() == TOK_SYNCH_SVC_PARAM )
			{
				*out_file << " = stmt_assign_synch_service_param (";
			}
			else if ( pda->getType() == TOK_BRIDGE_PARAM )
			{
				*out_file << " = stmt_assign_bridge_param (";
			}
			else if ( pda->getType() == TOK_TRANSFORMER_PARAM )
			{
				*out_file << " = stmt_assign_transform_param (";
			}
			*out_file << C_actn_var_name << ", \""
			<< pda->child()->getVcharText() << "\", "
			<< e2->getGenVarName() << ")" << endl;
			a->setGenVarName( var_name );
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

void GEN_SOR::break_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *b=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_BREAK) ) {
		_MATCH(TOK_STMT_BREAK);
		b=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_break ()" << endl ;
		b->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("break_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::bridge_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *be=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_BRIDGE) ) {
		
		vchar *kl;
		vchar *method;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_BRIDGE);
		s=(SORAST *)_t;
		_DOWN;
		be=(SORAST *)_t; bridge_expr(&_t,  &kl, &method );
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_bridge_void (\""
		<< kl << "\", \""
		<< method << "\", "
		<< be->getGenVarName() << ")" << endl;
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("bridge_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::continue_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *c=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTINUE) ) {
		_MATCH(TOK_STMT_CONTINUE);
		c=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_continue ()" << endl ;
		c->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("continue_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::control_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *stmt=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CONTROL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CONTROL);
		stmt=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_STOP);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_control (\"STOP\")" << endl ;
		stmt->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("control_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::create_event_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *erv=NULL;
	SORAST *es=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_EVENT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CREATE_EVENT);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_EVENT_REF_VAR);
		erv=(SORAST *)_t;
		_RIGHT;
		es=(SORAST *)_t; event_spec(&_t,  erv->getVcharText()  );
		_RESTORE;
		}
		_RIGHT;
		s->setGenVarName( es->getGenVarName() );   
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("create_event_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::create_object_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	SORAST *irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_CREATE_OBJECT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_CREATE_OBJECT);
		s=(SORAST *)_t;
		_DOWN;
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
		
		script_var_name var_name;
		if ( irv == 0 )
		{
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_create_obj_inst_no_var (\"" 
			<< kl->getVcharText() << "\")" << endl;
			s->setGenVarName( var_name );
		}
		else
		{
			script_var_name gen_name;
			if ( is_var_in_scope(irv->getVcharText()) )
			{
				get_gen_name( irv->getVcharText(), gen_name );
				irv->setGenVarName( gen_name );
			}
			else
			{
				next_var_var_name ( gen_name );
				declare_oir ( gen_name, irv->getVcharText(), kl->getVcharText() );
				add_var_to_scope( irv->getVcharText(), kl->getVcharText(), gen_name );
				irv->setGenVarName( gen_name );
			}

			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_create_obj_inst (" << irv->getGenVarName();
			if ( is_var_declared_in_scope(irv->getVcharText()) )
			*out_file << ", FALSE, \"";
			else
			*out_file << ", TRUE, \"";
			*out_file << kl->getVcharText() << "\")" << endl;
			set_var_declared_in_scope(irv->getVcharText());
			s->setGenVarName( var_name );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("create_object_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::delete_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_DELETE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_DELETE);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name gen_name;
		get_gen_name( irv->getVcharText(), gen_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_delete_obj_inst (" << gen_name
		<< ")" << endl;
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("delete_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::empty_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_EMPTY) ) {
		_MATCH(TOK_STMT_EMPTY);
		s=(SORAST *)_t;
		_RIGHT;
		s->setGenVarName( "DONT" );   
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("empty_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::for_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *irv1=NULL;
	SORAST *irv2=NULL;
	SORAST *vs=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_FOR) ) {
		
		script_var_name gen_name1;
		script_var_name prev_blck;   
		get_previous_block ( prev_blck ); 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_FOR);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv1=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_SET_VAR);
		irv2=(SORAST *)_t;
		_RIGHT;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_FOR);
		_DOWN;
		
		if ( is_var_in_scope(irv1->getVcharText()) )
		{
			get_gen_name( irv1->getVcharText(), gen_name1 );
			irv1->setGenVarName( gen_name1 );
		}
		else
		{
			next_var_var_name ( gen_name1 );
			vchar *iter_kl = get_key_letters ( irv2->getVcharText() );
			declare_oir ( gen_name1, irv1->getVcharText(), iter_kl );
			add_var_to_scope( irv1->getVcharText(), iter_kl, gen_name1 );
			irv1->setGenVarName( gen_name1 );
		}
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		new_scope();   
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				vs=(SORAST *)_t; valid_statement(&_t);
				add_valid_statement( vs->getGenVarName() );   
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("for_statement", _t);
			}
			}
		}
		}
		_MATCH(TOK_CONTEXT_POP);
		_RIGHT;
		
		delete_all_var_from_scope();
		drop_scope();
		_RESTORE;
		}
		_RIGHT;
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name gen_name2;
		get_gen_name( irv2->getVcharText(), gen_name2 );
		script_var_name last_blck;   
		get_previous_block ( last_blck ); 
		*out_file << ".Invoke " << var_name
		<< " = stmt_for (" << gen_name1;
		if ( is_var_declared_in_scope(irv1->getVcharText()) )
		*out_file << ", FALSE, ";
		else
		*out_file << ", TRUE, ";
		*out_file << gen_name2 << ", "
		<< last_blck << ")" << endl;
		set_var_declared_in_scope(irv1->getVcharText());
		s->setGenVarName( "DONT" );
		script_var_name blckn;
		next_blck_var_name ( blckn );
		*out_file << ".Invoke " << blckn << " = blck_append_stmt ("
		<< prev_blck << ", "
		<< var_name << ")" << endl;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("for_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::generate_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *es=NULL;
	SORAST *eiv=NULL;
	SORAST *aa=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_GENERATE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_GENERATE);
		s=(SORAST *)_t;
		_DOWN;
		if ( _t!=NULL && (_t->type()==TOK_EVENT_LABEL) ) {
			es=(SORAST *)_t; event_spec(&_t,  vcharGetEmptyString() );
			s->setGenVarName( es->getGenVarName() );   
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_EVENT_REF_VAR) ) {
			_MATCH(TOK_EVENT_REF_VAR);
			eiv=(SORAST *)_t;
			_RIGHT;
			
			script_var_name var_name;
			script_var_name gen_name;
			get_gen_name ( eiv->getVcharText(), gen_name );
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_generate_evt_inst (" << gen_name
			<< ")" << endl;
			s->setGenVarName( var_name );
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			aa=(SORAST *)_t; attribute_access(&_t);
			
			script_var_name var_name1;
			next_rval_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = rval_read_obj_attr (" << aa->getGenVarName() << ", \""
			<< aa->child()->getVcharText() << "\")" << endl;
			aa->setGenVarName( var_name1 );

			script_var_name var_name;
			next_stmt_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = stmt_generate_evt_inst_rval (" << aa->getGenVarName()
			<< ")" << endl;
			s->setGenVarName( var_name );
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

void GEN_SOR::if_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *e1=NULL;
	SORAST *vs=NULL;
	SORAST *e2=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_IF) ) {
		
		script_var_name prev_blck;   
		get_previous_block ( prev_blck ); 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_IF);
		s=(SORAST *)_t;
		_DOWN;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_IF);
		_DOWN;
		e1=(SORAST *)_t; expr(&_t);
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		new_scope();   
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				vs=(SORAST *)_t; valid_statement(&_t);
				add_valid_statement( vs->getGenVarName() );   
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
		
		delete_all_var_from_scope();
		drop_scope();
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name last_blck;   
		get_previous_block ( last_blck ); 
		*out_file << ".Invoke " << var_name
		<< " = stmt_if (" << e1->getGenVarName() << ", "
		<< last_blck << ")" << endl;
		s->setGenVarName( "DONT" );
		script_var_name blckn;
		next_blck_var_name ( blckn );
		*out_file << ".Invoke " << blckn << " = blck_append_stmt ("
		<< prev_blck << ", "
		<< var_name << ")" << endl;
		strcpy ( prev_blck, blckn );
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_CLAUSE_ELIF) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_CLAUSE_ELIF);
				_DOWN;
				e2=(SORAST *)_t; expr(&_t);
				_MATCH(TOK_CONTEXT_PUSH);
				_RIGHT;
				new_scope();   
				{int _done=0;
				while ( !_done ) {
					if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
					_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
					_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
					_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
					_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
					_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
					_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
					_t->type()==TOK_STMT_WHILE) ) {
						vs=(SORAST *)_t; valid_statement(&_t);
						add_valid_statement( vs->getGenVarName() );   
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
				
				delete_all_var_from_scope();
				drop_scope();
				_RESTORE;
				}
				_RIGHT;
				
				script_var_name var_name;
				next_stmt_var_name ( var_name );
				script_var_name last_blck;   
				get_previous_block ( last_blck ); 
				*out_file << ".Invoke " << var_name
				<< " = stmt_elif (" << e2->getGenVarName() << ", "
				<< last_blck << ")" << endl;
				script_var_name blckn;
				next_blck_var_name ( blckn );
				*out_file << ".Invoke " << blckn << " = blck_append_stmt ("
				<< prev_blck << ", "
				<< var_name << ")" << endl;
				strcpy ( prev_blck, blckn );
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
			_DOWN;
			_MATCH(TOK_CONTEXT_PUSH);
			_RIGHT;
			new_scope();   
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
				_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
				_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
				_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
				_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
				_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
				_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
				_t->type()==TOK_STMT_WHILE) ) {
					vs=(SORAST *)_t; valid_statement(&_t);
					add_valid_statement( vs->getGenVarName() );   
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
			
			delete_all_var_from_scope();
			drop_scope();
			_RESTORE;
			}
			_RIGHT;
			
			script_var_name var_name;
			next_stmt_var_name ( var_name );
			script_var_name last_blck;   
			get_previous_block ( last_blck ); 
			*out_file << ".Invoke " << var_name
			<< " = stmt_else ("
			<< last_blck << ")" << endl;
			script_var_name blckn;
			next_blck_var_name ( blckn );
			*out_file << ".Invoke " << blckn << " = blck_append_stmt ("
			<< prev_blck << ", "
			<< var_name << ")" << endl;
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("if_statement", _t);
		}
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

void GEN_SOR::relate_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *irv1=NULL;
	SORAST *irv2=NULL;
	SORAST *rn=NULL;
	SORAST *ph=NULL;
	SORAST *irv3=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_RELATE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_RELATE);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv1=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_VAR);
		irv2=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_RELID);
		rn=(SORAST *)_t;
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
			irv3=(SORAST *)_t;
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
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name gen_name1;
		get_gen_name( irv1->getVcharText(), gen_name1 );
		script_var_name gen_name2;
		get_gen_name( irv2->getVcharText(), gen_name2 );
		const vchar *rel_num = rn->getVcharText();
		rel_num += 1;   // skip over the 'R'
		if ( irv3 == 0 )
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_relate (" << gen_name1
			<< ", " << gen_name2
			<< ", " << rel_num << ", \"";
			if ( ph != 0 )
			{
				Description ticked_str(ph->getVcharText());
				t_uint ticked_str_cursor = 0;
				Description unticked_str;
				ticked_str.parse_token__ticked_str(ticked_str_cursor, unticked_str);
				*out_file << unticked_str.char_ptr();
			}
			*out_file << "\")" << endl ;
		}
		else
		{
			script_var_name gen_name3;
			get_gen_name( irv3->getVcharText(), gen_name3 );
			*out_file << ".Invoke " << var_name
			<< " = stmt_relate_using (" << gen_name1
			<< ", " << gen_name2
			<< ", " << rel_num
			<< ", " << gen_name3 << ", \"";
			if ( ph != 0 )
			{
				Description ticked_str(ph->getVcharText());
				t_uint ticked_str_cursor = 0;
				Description unticked_str;
				ticked_str.parse_token__ticked_str(ticked_str_cursor, unticked_str);
				*out_file << unticked_str.char_ptr();
			}
			*out_file << "\")" << endl ;
		}
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("relate_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::return_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *e=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_RETURN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_RETURN);
		s=(SORAST *)_t;
		_DOWN;
		if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
			e=(SORAST *)_t; expr(&_t);
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
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		if ( e == 0 )
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_return_void()" << endl;
		}
		else
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_return_rval(" << e->getGenVarName() << ")" << endl;
		}
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("return_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::select_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *irv=NULL;
	SORAST *os=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ONE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_SELECT_ONE);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_RIGHT;
		os=(SORAST *)_t; object_spec(&_t,  "ONE", irv );
		_RESTORE;
		}
		_RIGHT;
		s->setGenVarName( os->getGenVarName() );   
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_ANY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_SELECT_ANY);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_RIGHT;
		os=(SORAST *)_t; object_spec(&_t,  "ANY", irv );
		_RESTORE;
		}
		_RIGHT;
		s->setGenVarName( os->getGenVarName() );   
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STMT_SELECT_MANY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_SELECT_MANY);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_SET_VAR);
		irv=(SORAST *)_t;
		_RIGHT;
		os=(SORAST *)_t; object_spec(&_t,  "MANY", irv );
		_RESTORE;
		}
		_RIGHT;
		s->setGenVarName( os->getGenVarName() );   
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_statement", _t);
	}
	}
	}
	*_root = _t;
}

void GEN_SOR::synch_svc_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *sse=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_SYNCH_SVC) ) {
		
		vchar *method;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_SYNCH_SVC);
		s=(SORAST *)_t;
		_DOWN;
		sse=(SORAST *)_t; synch_svc_expr(&_t,  &method );
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_synch_service_void (\""
		<< method << "\", "
		<< sse->getGenVarName() << ")" << endl;
		s->setGenVarName( var_name );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("synch_svc_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::transform_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *te=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_TRANSFORM) ) {
		
		vchar *kl;
		vchar *method;
		bool instance_based;
		script_var_name irv_gen_name;   // i2946.2.3 changed
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_TRANSFORM);
		s=(SORAST *)_t;
		_DOWN;
		te=(SORAST *)_t; transformer_expr(&_t,  &kl, &method, &instance_based, irv_gen_name );
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		if ( instance_based )
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_transform_instance_void ("
			<< irv_gen_name << ", \""
			<< method << "\", "
			<< te->getGenVarName() << ")" << endl;
		}
		else
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_transform_void (\""
			<< kl << "\", \""
			<< method << "\", "
			<< te->getGenVarName() << ")" << endl;
		}
		s->setGenVarName( var_name );
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

void GEN_SOR::unrelate_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *irv1=NULL;
	SORAST *irv2=NULL;
	SORAST *rn=NULL;
	SORAST *ph=NULL;
	SORAST *irv3=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_UNRELATE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_UNRELATE);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_INST_REF_VAR);
		irv1=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_INST_REF_VAR);
		irv2=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_RELID);
		rn=(SORAST *)_t;
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
			irv3=(SORAST *)_t;
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
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name gen_name1;
		get_gen_name( irv1->getVcharText(), gen_name1 );
		script_var_name gen_name2;
		get_gen_name( irv2->getVcharText(), gen_name2 );
		const vchar *rel_num = rn->getVcharText();
		rel_num += 1;   // skip over the 'R'
		if ( irv3 == 0 )
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_unrelate (" << gen_name1
			<< ", " << gen_name2
			<< ", " << rel_num << ", \"";
			if ( ph != 0 )
			{
				Description ticked_str(ph->getVcharText());
				t_uint ticked_str_cursor = 0;
				Description unticked_str;
				ticked_str.parse_token__ticked_str(ticked_str_cursor, unticked_str);
				*out_file << unticked_str.char_ptr();
			}
			*out_file << "\")" << endl ;
		}
		else
		{
			script_var_name gen_name3;
			get_gen_name( irv3->getVcharText(), gen_name3 );
			*out_file << ".Invoke " << var_name
			<< " = stmt_unrelate_using (" << gen_name1
			<< ", " << gen_name2
			<< ", " << rel_num
			<< ", " << gen_name3 << ", \"";
			if ( ph != 0 )
			{
				Description ticked_str(ph->getVcharText());
				t_uint ticked_str_cursor = 0;
				Description unticked_str;
				ticked_str.parse_token__ticked_str(ticked_str_cursor, unticked_str);
				*out_file << unticked_str.char_ptr();
			}
			*out_file << "\")" << endl ;
		}
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("unrelate_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::while_statement(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *e=NULL;
	SORAST *vs=NULL;
	if ( _t!=NULL && (_t->type()==TOK_STMT_WHILE) ) {
		
		script_var_name prev_blck;   
		get_previous_block ( prev_blck ); 
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_STMT_WHILE);
		s=(SORAST *)_t;
		_DOWN;
		e=(SORAST *)_t; expr(&_t);
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CLAUSE_WHILE);
		_DOWN;
		_MATCH(TOK_CONTEXT_PUSH);
		_RIGHT;
		new_scope();   
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_STMT_ASSIGN||_t->type()==TOK_STMT_BREAK||
			_t->type()==TOK_STMT_BRIDGE||_t->type()==TOK_STMT_CONTINUE||_t->type()==TOK_STMT_CONTROL||
			_t->type()==TOK_STMT_CREATE_EVENT||_t->type()==TOK_STMT_CREATE_OBJECT||_t->type()==TOK_STMT_DELETE||
			_t->type()==TOK_STMT_EMPTY||_t->type()==TOK_STMT_FOR||_t->type()==TOK_STMT_GENERATE||
			_t->type()==TOK_STMT_IF||_t->type()==TOK_STMT_RELATE||_t->type()==TOK_STMT_RETURN||
			_t->type()==TOK_STMT_SELECT_ONE||_t->type()==TOK_STMT_SELECT_ANY||_t->type()==TOK_STMT_SELECT_MANY||
			_t->type()==TOK_STMT_SYNCH_SVC||_t->type()==TOK_STMT_TRANSFORM||_t->type()==TOK_STMT_UNRELATE||
			_t->type()==TOK_STMT_WHILE) ) {
				vs=(SORAST *)_t; valid_statement(&_t);
				add_valid_statement( vs->getGenVarName() );   
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_CONTEXT_POP) ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("while_statement", _t);
			}
			}
		}
		}
		_MATCH(TOK_CONTEXT_POP);
		_RIGHT;
		
		delete_all_var_from_scope();
		drop_scope();
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_stmt_var_name ( var_name );
		script_var_name last_blck;   
		get_previous_block ( last_blck ); 
		*out_file << ".Invoke " << var_name
		<< " = stmt_while (" << e->getGenVarName() << ", "
		<< last_blck << ")" << endl;
		script_var_name blckn;
		next_blck_var_name ( blckn );
		*out_file << ".Invoke " << blckn << " = blck_append_stmt("
		<< prev_blck << ", "
		<< var_name << ")" << endl;
		s->setGenVarName( "DONT" );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("while_statement", _t);
	}
	*_root = _t;
}

void GEN_SOR::event_spec(SORASTBase **_root,  const vchar *event_ref_var  )
{
	SORASTBase *_t = *_root;
	SORAST *event=NULL;
	SORAST *em=NULL;
	SORAST *kla=NULL;
	SORAST *klc=NULL;
	SORAST *irv=NULL;
	SORAST *klee=NULL;
	SORAST *nm=NULL;
	SORAST *ex=NULL;
	if ( _t!=NULL && (_t->type()==TOK_EVENT_LABEL) ) {
		
		script_var_name var_name1;
		script_var_name var_name2;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_EVENT_LABEL);
		event=(SORAST *)_t;
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
			em=(SORAST *)_t;
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
			
			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_evt_assigner (\""
			<< event->getVcharText() << "\")" << endl;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_KL_OBJECT_CREATOR) ) {
			_MATCH(TOK_KL_OBJECT_CREATOR);
			klc=(SORAST *)_t;
			_RIGHT;
			
			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_evt_creation (\""
			<< event->getVcharText() << "\")" << endl;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
			
			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_evt_obj_inst (\""
			<< event->getVcharText() << "\")" << endl;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_KL_EXTERNAL_ENTITY) ) {
			_MATCH(TOK_KL_EXTERNAL_ENTITY);
			klee=(SORAST *)_t;
			_RIGHT;
			
			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_evt_ext_entity (\""
			<< event->getVcharText() << "\")" << endl;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("event_spec", _t);
		}
		}
		}
		}
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_SUPP_DATA_NAME) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_SUPP_DATA_NAME);
				nm=(SORAST *)_t;
				_DOWN;
				ex=(SORAST *)_t; expr(&_t);
				_RESTORE;
				}
				_RIGHT;
				
				next_param_var_name ( var_name2 );
				*out_file << ".Invoke " << var_name2
				<< " = param_add (" << var_name1 << ", \""
				<< nm->getVcharText() << "\", "
				<< ex->getGenVarName() << ")" << endl ;
				strcpy ( var_name1, var_name2 );
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
		
		next_param_var_name ( var_name2 );
		*out_file << ".Invoke " << var_name2
		<< " = param_end (" << var_name1
		<< ")" << endl ;
		strcpy ( var_name1, var_name2 );

		next_stmt_var_name ( var_name2 );
		if ( vcharCompare( event_ref_var, vcharGetEmptyString() ) == 0 )
		{
			if ( irv != 0 )
			{
				script_var_name irv_gen_name;
				get_gen_name ( irv->getVcharText(), irv_gen_name );
				*out_file << ".Invoke " << var_name2
				<< " = stmt_generate_obj_inst (\""
				<< event->getVcharText() << "\", "
				<< var_name1 << ", "
				<< irv_gen_name << ")" << endl;
			}
			else if ( kla != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_generate_assigner (\""
				<< event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< kla->getVcharText() << "\")" << endl;
			}
			else if ( klc != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_generate_creation (\""
				<< event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< klc->getVcharText() << "\")" << endl;
			}
			else if ( klee != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_generate_ext_entity (\""
				<< event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< klee->getVcharText() << "\")" << endl;
			}
		}
		else
		{
			script_var_name erv_gen_name;
			if ( is_var_in_scope(event_ref_var) )
			{
				get_gen_name( event_ref_var, erv_gen_name );
			}
			else
			{
				next_var_var_name ( erv_gen_name );
				if ( irv != 0 )
				{
					declare_ei ( erv_gen_name, event_ref_var );
					vchar *evt_kl = get_key_letters ( irv->getVcharText() );
					add_var_to_scope( event_ref_var, evt_kl, erv_gen_name );
				}
				else if ( kla != 0 )
				{
					declare_ei ( erv_gen_name, event_ref_var );
					add_var_to_scope( event_ref_var, kla->getVcharText(), erv_gen_name );
				}
				else if ( klc != 0 )
				{
					declare_ei ( erv_gen_name, event_ref_var );
					add_var_to_scope( event_ref_var, klc->getVcharText(), erv_gen_name );
				}
				else if ( klee != 0 )
				{
					declare_ei ( erv_gen_name, event_ref_var );
					add_var_to_scope( event_ref_var, klee->getVcharText(), erv_gen_name );
				}
			}

			if ( irv != 0 )
			{
				script_var_name irv_gen_name;
				get_gen_name ( irv->getVcharText(), irv_gen_name );
				*out_file << ".Invoke " << var_name2
				<< " = stmt_create_evt_obj_inst ("
				<< erv_gen_name << ", ";
				if ( is_var_declared_in_scope(event_ref_var) )
				*out_file << "FALSE, \"";
				else
				*out_file << "TRUE, \"";
				*out_file << event->getVcharText() << "\", "
				<< var_name1 << ", "
				<< irv_gen_name << ")" << endl;
				set_var_declared_in_scope(event_ref_var);
			}
			else if ( kla != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_create_evt_assigner ("
				<< erv_gen_name << ", ";
				if ( is_var_declared_in_scope(event_ref_var) )
				*out_file << "FALSE, \"";
				else
				*out_file << "TRUE, \"";
				*out_file << event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< kla->getVcharText() << "\")" << endl;
				set_var_declared_in_scope(event_ref_var);
			}
			else if ( klc != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_create_evt_creation ("
				<< erv_gen_name << ", ";
				if ( is_var_declared_in_scope(event_ref_var) )
				*out_file << "FALSE, \"";
				else
				*out_file << "TRUE, \"";
				*out_file << event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< klc->getVcharText() << "\")" << endl;
				set_var_declared_in_scope(event_ref_var);
			}
			else if ( klee != 0 )
			{
				*out_file << ".Invoke " << var_name2
				<< " = stmt_create_evt_ext_entity ("
				<< erv_gen_name << ", ";
				if ( is_var_declared_in_scope(event_ref_var) )
				*out_file << "FALSE, \"";
				else
				*out_file << "TRUE, \"";
				*out_file << event->getVcharText() << "\", "
				<< var_name1 << ", \""
				<< klee->getVcharText() << "\")" << endl;
				set_var_declared_in_scope(event_ref_var);
			}
		}

		event->setGenVarName( var_name2 );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("event_spec", _t);
	}
	*_root = _t;
}

void GEN_SOR::instance_chain(SORASTBase **_root,  char *card, bool wc  )
{
	SORASTBase *_t = *_root;
	SORAST *ic=NULL;
	SORAST *irv=NULL;
	SORAST *irsv=NULL;
	SORAST *kl=NULL;
	SORAST *rn=NULL;
	SORAST *ph=NULL;
	if ( _t!=NULL && (_t->type()==TOK_INST_REF) ) {
		_MATCH(TOK_INST_REF);
		ic=(SORAST *)_t;
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
			_MATCH(TOK_INST_REF_VAR);
			irv=(SORAST *)_t;
			_RIGHT;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_INST_REF_SET_VAR) ) {
			_MATCH(TOK_INST_REF_SET_VAR);
			irsv=(SORAST *)_t;
			_RIGHT;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("instance_chain", _t);
		}
		}
		
		script_var_name var_name1;
		script_var_name var_name2;
		next_chain_var_name ( var_name1 );
		script_var_name inst_gen_name;
		if ( irv != 0 )
		{
			get_gen_name( irv->getVcharText(), inst_gen_name );
		}
		else if ( irsv != 0 )
		{
			get_gen_name( irsv->getVcharText(), inst_gen_name );
		}

		*out_file << ".Invoke " << var_name1
		<< " = chain_begin (\"" << card << "\", "
		<< inst_gen_name << ", "; 
		if ( wc )             
		*out_file << "TRUE)" << endl ;
		else
		*out_file << "FALSE)" << endl ;

		{int _done=0;
		do {
			if ( _t!=NULL && (_t->type()==TOK_KL_OBJECT) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_KL_OBJECT);
				kl=(SORAST *)_t;
				_DOWN;
				_MATCH(TOK_RELID);
				rn=(SORAST *)_t;
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
				_RESTORE;
				}
				_RIGHT;
				
				next_chain_var_name ( var_name2 );

				const vchar *rel_num = rn->getVcharText();
				rel_num += 1;   // skip over the 'R'

				*out_file << ".Invoke " << var_name2
				<< " = chain_add_link (" << var_name1 << ", \""
				<< kl->getVcharText() << "\", "
				<< rel_num << ", \"";
				if ( ph != 0 )
				{
					Description ticked_str(ph->getVcharText());
					t_uint ticked_str_cursor = 0;
					Description unticked_str;
					ticked_str.parse_token__ticked_str(ticked_str_cursor, unticked_str);
					*out_file << unticked_str.char_ptr();
				}
				*out_file << "\")" << endl ;
				strcpy ( var_name1, var_name2 );
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
		
		next_chain_var_name ( var_name2 );
		*out_file << ".Invoke " << var_name2
		<< " = chain_end (" << var_name1
		<< ")" << endl ;
		ic->setGenVarName( var_name2 );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("instance_chain", _t);
	}
	*_root = _t;
}

void GEN_SOR::object_spec(SORASTBase **_root, char *card, SORAST *irv )
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_RELATED) ) {
		select_nowhere(&_t,  card, irv );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_RELATED_WHERE) ) {
		select_where(&_t,  card, irv );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_FROM) ) {
		select_from(&_t,  card, irv );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("object_spec", _t);
	}
	}
	}
	*_root = _t;
}

void GEN_SOR::select_nowhere(SORASTBase **_root, char *card, SORAST *irv  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RELATED) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_RELATED);
		s=(SORAST *)_t;
		_DOWN;
		kl=(SORAST *)_t; instance_chain(&_t,  card, FALSE );
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name gen_name;
		if ( is_var_in_scope(irv->getVcharText()) )
		{
			get_gen_name( irv->getVcharText(), gen_name );
			irv->setGenVarName( gen_name );
		}
		else
		{
			next_var_var_name ( gen_name );
			if ( strcmp ( card, "MANY" ) != 0 )
			{
				declare_oir( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			else
			{
				declare_oirs( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			add_var_to_scope( irv->getVcharText(), kl->getVcharText(), gen_name );

			irv->setGenVarName( gen_name );
		}

		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_select_related_by (\""
		<< card << "\", "
		<< irv->getGenVarName();
		if ( is_var_declared_in_scope(irv->getVcharText()) )
		*out_file << ", FALSE, ";
		else
		*out_file << ", TRUE, ";
		*out_file << kl->getGenVarName() << ")" << endl;
		
       set_var_declared_in_scope(irv->getVcharText());
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_nowhere", _t);
	}
	*_root = _t;
}

void GEN_SOR::select_where(SORASTBase **_root, char *card, SORAST *irv  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	SORAST *tw=NULL;
	SORAST *wc=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RELATED_WHERE) ) {
		
		script_var_name where1;
		script_var_name where2;
		Special_Where *sw = 0;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_RELATED_WHERE);
		s=(SORAST *)_t;
		_DOWN;
		kl=(SORAST *)_t; instance_chain(&_t,  card, TRUE );
		_RESTORE;
		}
		_RIGHT;
		_MATCH(TOK_WHERE);
		tw=(SORAST *)_t;
		_RIGHT;
		
		next_where_var_name ( where1 );
		*out_file << ".Invoke " << where1
		<< " = where_begin (\""
		<< kl->getVcharText() << "\")" << endl;

		SORAST *ex = tw->sibling();
		sw = Special_Where::match ( 
		G_Special_Where_table, kl->getVcharText(),ex );

		if ( sw )
		{
			ex->setType(TOK_SPECIAL_WHERE);
			special_where_invokes ( sw );
		}         
		if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
			wc=(SORAST *)_t; expr(&_t);
			
			next_where_var_name ( where2 );
			*out_file << ".Invoke " << where2
			<< " = where_add_normal (" << where1 << ", "
			<< wc->getGenVarName() << ")" << endl;
		}
		else {
		if ( _t!=NULL && (_t->type()==TOK_SPECIAL_WHERE) ) {
			_MATCH(TOK_SPECIAL_WHERE);
			_RIGHT;
			
			next_where_var_name ( where2 );
			script_var_name param_var_name;
			get_previous_param(param_var_name);
			*out_file << ".Invoke " << where2
			<< " = where_add_special (" << where1 << ", \""
			<< sw->key << "\", " 
			<< param_var_name << ")" << endl;
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("select_where", _t);
		}
		}
		
		script_var_name where3;
		next_where_var_name ( where3 );
		*out_file << ".Invoke " << where3
		<< " = where_end (" << where2 << ")" << endl;

		script_var_name gen_name;
		if ( is_var_in_scope(irv->getVcharText()) )
		{
			get_gen_name( irv->getVcharText(), gen_name );
			irv->setGenVarName( gen_name );
		}
		else
		{
			next_var_var_name ( gen_name );
			if ( strcmp ( card, "MANY" ) != 0 )
			{
				declare_oir( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			else
			{
				declare_oirs( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			add_var_to_scope( irv->getVcharText(), kl->getVcharText(), gen_name );

			irv->setGenVarName( gen_name );
		}

		script_var_name var_name;
		next_stmt_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = stmt_select_related_by_where (\""
		<< card << "\", "
		<< irv->getGenVarName();
		if ( is_var_declared_in_scope(irv->getVcharText()) )
		*out_file << ", FALSE, ";
		else
		*out_file << ", TRUE, ";
		*out_file << kl->getGenVarName() << ", "
		<< where3 << ")" << endl;
		
       set_var_declared_in_scope(irv->getVcharText());
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_where", _t);
	}
	*_root = _t;
}

void GEN_SOR::select_from(SORASTBase **_root, char *card, SORAST *irv  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	SORAST *tw=NULL;
	SORAST *wc=NULL;
	if ( _t!=NULL && (_t->type()==TOK_FROM) ) {
		
		script_var_name where1;
		Special_Where *sw = 0;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_FROM);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_KL_OBJECT);
		kl=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		if ( _t!=NULL && (_t->type()==TOK_WHERE) ) {
			_MATCH(TOK_WHERE);
			tw=(SORAST *)_t;
			_RIGHT;
			
			next_where_var_name ( where1 );
			*out_file << ".Invoke " << where1
			<< " = where_begin (\""
			<< kl->getVcharText() << "\")" << endl;

			SORAST *ex = tw->sibling();
			sw = Special_Where::match ( 
			G_Special_Where_table, kl->getVcharText(), ex );

			if ( sw )
			{
				ex->setType(TOK_SPECIAL_WHERE);
				special_where_invokes ( sw );
			}         
			if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
				wc=(SORAST *)_t; expr(&_t);
			}
			else {
			if ( _t!=NULL && (_t->type()==TOK_SPECIAL_WHERE) ) {
				_MATCH(TOK_SPECIAL_WHERE);
				_RIGHT;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("select_from", _t);
			}
			}
		}
		else {
		if ( _t==NULL ) {
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("select_from", _t);
		}
		}
		
		script_var_name gen_name;
		if ( is_var_in_scope(irv->getVcharText()) )
		{
			get_gen_name( irv->getVcharText(), gen_name );
			irv->setGenVarName( gen_name );
		}
		else
		{
			next_var_var_name ( gen_name );
			if ( strcmp ( card, "MANY" ) != 0 )
			{
				declare_oir( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			else
			{
				declare_oirs( gen_name, irv->getVcharText(), kl->getVcharText() );
			}
			add_var_to_scope( irv->getVcharText(), kl->getVcharText(), gen_name );

			irv->setGenVarName( gen_name );
		}

		script_var_name var_name;
		next_stmt_var_name ( var_name );
		if ( wc == 0 && sw == 0 )
		{
			*out_file << ".Invoke " << var_name
			<< " = stmt_select_from_instances_of (\""
			<< card << "\", "
			<< irv->getGenVarName();
			if ( is_var_declared_in_scope(irv->getVcharText()) )
			*out_file << ", FALSE, \"";
			else
			*out_file << ", TRUE, \"";
			*out_file << kl->getVcharText() << "\")" << endl;
		}
		else
		{
			script_var_name where2;
			next_where_var_name ( where2 );
			if ( wc != 0 )
			{
				*out_file << ".Invoke " << where2
				<< " = where_add_normal (" << where1 << ", "
				<< wc->getGenVarName() << ")" << endl;
			}
			else
			{
				script_var_name param_var_name;
				get_previous_param(param_var_name);
				*out_file << ".Invoke " << where2
				<< " = where_add_special (" << where1 << ", \""
				<< sw->key << "\", " 
				<< param_var_name << ")" << endl;
			}

			script_var_name where3;
			next_where_var_name ( where3 );
			*out_file << ".Invoke " << where3
			<< " = where_end (" << where2 << ")" << endl;

			*out_file << ".Invoke " << var_name
			<< " = stmt_select_from_instances_of_where (\""
			<< card << "\", "
			<< irv->getGenVarName();
			if ( is_var_declared_in_scope(irv->getVcharText()) )
			*out_file << ", FALSE, \"";
			else
			*out_file << ", TRUE, \"";
			*out_file << kl->getVcharText() << "\", "
			<< where3 << ")" << endl;
		}
		set_var_declared_in_scope(irv->getVcharText());
		s->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("select_from", _t);
	}
	*_root = _t;
}

void GEN_SOR::expr(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *e=NULL;
	SORAST *se=NULL;
	if ( _t!=NULL && (_t->type()==TOK_EXPRESSION) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_EXPRESSION);
		e=(SORAST *)_t;
		_DOWN;
		se=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		e->setGenVarName( se->getGenVarName() );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("expr", _t);
	}
	*_root = _t;
}

void GEN_SOR::sub_expr(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
	_t->type()==TOK_UNARY_PLUS||_t->type()==TOK_UNARY_MINUS||_t->type()==TOK_PAREN_EXPR||
	_t->type()==TOK_CARDINALITY||_t->type()==TOK_EMPTY||_t->type()==TOK_NOTEMPTY||
	_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||
	_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN||_t->type()==TOK_ENUMERATION||
	_t->type()==TOK_RCVD_EVT||_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_TRANSFORMER_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR||
	_t->type()==TOK_BRIDGE_EXPR||_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		term(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_AND) ) {
		op_and(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_OR) ) {
		op_or(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_DOUBLEEQUAL||_t->type()==TOK_NOTEQUAL||
	_t->type()==TOK_LESSTHAN||_t->type()==TOK_LE||_t->type()==TOK_GT||
	_t->type()==TOK_GE) ) {
		op_relational(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_PLUS||_t->type()==TOK_MINUS) ) {
		op_addition(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_NOT) ) {
		op_boolean_negation(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TIMES||_t->type()==TOK_DIV||
	_t->type()==TOK_MOD) ) {
		op_multiplication(&_t);
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
	*_root = _t;
}

void GEN_SOR::op_and(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	if ( _t!=NULL && (_t->type()==TOK_AND) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_AND);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"AND\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_and", _t);
	}
	*_root = _t;
}

void GEN_SOR::op_or(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *o=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	if ( _t!=NULL && (_t->type()==TOK_OR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_OR);
		o=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"OR\", "
		<< s2->getGenVarName() << ")" << endl;
		o->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_or", _t);
	}
	*_root = _t;
}

void GEN_SOR::op_relational(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	if ( _t!=NULL && (_t->type()==TOK_DOUBLEEQUAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_DOUBLEEQUAL);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"==\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_NOTEQUAL) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_NOTEQUAL);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"!=\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_LESSTHAN) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_LESSTHAN);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"<\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_LE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_LE);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"<=\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_GT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_GT);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \">\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_GE) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_GE);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \">=\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
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
	*_root = _t;
}

void GEN_SOR::op_addition(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *p=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	SORAST *m=NULL;
	if ( _t!=NULL && (_t->type()==TOK_PLUS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_PLUS);
		p=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"+\", "
		<< s2->getGenVarName() << ")" << endl;
		p->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_MINUS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_MINUS);
		m=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"-\", "
		<< s2->getGenVarName() << ")" << endl;
		m->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_addition", _t);
	}
	}
	*_root = _t;
}

void GEN_SOR::op_boolean_negation(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *s1=NULL;
	if ( _t!=NULL && (_t->type()==TOK_NOT) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_NOT);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"NOT\", "
		<< s1->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_boolean_negation", _t);
	}
	*_root = _t;
}

void GEN_SOR::op_multiplication(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *s1=NULL;
	SORAST *s2=NULL;
	if ( _t!=NULL && (_t->type()==TOK_TIMES) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_TIMES);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"*\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_DIV) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_DIV);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"/\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_MOD) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_MOD);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; sub_expr(&_t);
		s2=(SORAST *)_t; sub_expr(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_binary_op ("
		<< s1->getGenVarName() << ", \"%\", "
		<< s2->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("op_multiplication", _t);
	}
	}
	}
	*_root = _t;
}

void GEN_SOR::term(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *a=NULL;
	SORAST *s1=NULL;
	if ( _t!=NULL && (_t->type()==TOK_UNARY_PLUS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_UNARY_PLUS);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; term(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"+\", "
		<< s1->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_UNARY_MINUS) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_UNARY_MINUS);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; term(&_t);
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"-\", "
		<< s1->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_PAREN_EXPR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_PAREN_EXPR);
		a=(SORAST *)_t;
		_DOWN;
		s1=(SORAST *)_t; expr(&_t);
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_add_parens ("
		<< s1->getGenVarName() << ")" << endl;
		a->setGenVarName( var_name );
		_RESTORE;
		}
		_RIGHT;
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_CARDINALITY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_CARDINALITY);
		a=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_LOCAL_VAR);
		s1=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		script_var_name gen_name;
		get_gen_name( s1->getVcharText(), gen_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"CARDINALITY\", "
		<< gen_name << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_EMPTY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_EMPTY);
		a=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_LOCAL_VAR);
		s1=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		script_var_name gen_name;
		get_gen_name( s1->getVcharText(), gen_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"EMPTY\", "
		<< gen_name << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_NOTEMPTY) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_NOTEMPTY);
		a=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_LOCAL_VAR);
		s1=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		script_var_name gen_name;
		get_gen_name( s1->getVcharText(), gen_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_unary_op (\"NOT_EMPTY\", "
		<< gen_name << ")" << endl;
		a->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR||_t->type()==TOK_INST_REF_VAR||
	_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||_t->type()==TOK_STRING||
	_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN||_t->type()==TOK_ENUMERATION||
	_t->type()==TOK_RCVD_EVT||_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_TRANSFORMER_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM||_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR||
	_t->type()==TOK_BRIDGE_EXPR||_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		rval(&_t);
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
	*_root = _t;
}

void GEN_SOR::rval(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *aa=NULL;
	SORAST *be=NULL;
	SORAST *te=NULL;
	SORAST *sse=NULL;
	SORAST *v=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RCVD_EVT) ) {
		event_data_access(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_PARAM||_t->type()==TOK_TRANSFORMER_PARAM||
	_t->type()==TOK_SYNCH_SVC_PARAM) ) {
		param_data_access(&_t,   TRUE  );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
		aa=(SORAST *)_t; attribute_access(&_t);
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		if ( is_selected (aa->getGenVarName()) )
		{
			*out_file << ".Invoke " << var_name
			<< " = rval_read_selected_attr (" << aa->getGenVarName() << ", \""
			<< aa->child()->getVcharText() << "\")" << endl;
		}
		else
		{
			*out_file << ".Invoke " << var_name
			<< " = rval_read_obj_attr (" << aa->getGenVarName() << ", \""
			<< aa->child()->getVcharText() << "\")" << endl;
		}
		aa->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_EXPR) ) {
		
		vchar *kl;
		vchar *method;
		be=(SORAST *)_t; bridge_expr(&_t,  &kl, &method );
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_bridge (\""
		<< kl << "\", \""
		<< method << "\", "
		<< be->getGenVarName() << ")" << endl;
		be->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR) ) {
		
		vchar *kl;
		vchar *method;
		bool instance_based;
		script_var_name irv_gen_name;   // i2946.2.3 changed
		te=(SORAST *)_t; transformer_expr(&_t,  &kl, &method, &instance_based, irv_gen_name );
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		if ( instance_based )
		{
			*out_file << ".Invoke " << var_name
			<< " = rval_transform_instance ("
			<< irv_gen_name << ", \""
			<< method << "\", "
			<< te->getGenVarName() << ")" << endl;
		}
		else
		{
			*out_file << ".Invoke " << var_name
			<< " = rval_transform (\""
			<< kl << "\", \""
			<< method << "\", "
			<< te->getGenVarName() << ")" << endl;
		}
		te->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		
		vchar *method;
		sse=(SORAST *)_t; synch_svc_expr(&_t,  &method );
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_synch_service (\""
		<< method << "\", "
		<< sse->getGenVarName() << ")" << endl;
		sse->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_FRACTION||_t->type()==TOK_NUMBER||
	_t->type()==TOK_STRING||_t->type()==TOK_TRUETOKEN||_t->type()==TOK_FALSETOKEN) ) {
		constant_value(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_ENUMERATION) ) {
		enumerator_literal(&_t);
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_LOCAL_VAR) ) {
		_MATCH(TOK_LOCAL_VAR);
		v=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		script_var_name gen_name;
		get_gen_name( v->getVcharText(), gen_name );
		if ( v->getDatatype() == OBJECT_INST_REF_DATATYPE )
		{
			C_last_resort_key_letters = get_key_letters( v->getVcharText() );
		}
		if ( v->getDatatype() == OBJECT_INST_REF_SET_DATATYPE )
		{
			C_last_resort_key_letters = get_key_letters( v->getVcharText() );
		}
		*out_file << ".Invoke " << var_name
		<< " = rval_read_transient_var (" << gen_name
		<< ")" << endl;
		v->setGenVarName( var_name );
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

void GEN_SOR::constant_value(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *f=NULL;
	SORAST *n=NULL;
	SORAST *s=NULL;
	SORAST *t=NULL;
	if ( _t!=NULL && (_t->type()==TOK_FRACTION) ) {
		_MATCH(TOK_FRACTION);
		f=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_real (\"" << f->getVcharText()
		<< "\")" << endl;
		f->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_NUMBER) ) {
		_MATCH(TOK_NUMBER);
		n=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_integer (\"" << n->getVcharText()
		<< "\")" << endl;
		n->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_STRING) ) {
		_MATCH(TOK_STRING);
		s=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_string (\"" << s->getVcharText()
		<< "\")" << endl;
		s->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRUETOKEN) ) {
		_MATCH(TOK_TRUETOKEN);
		t=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_boolean (\"TRUE\")" << endl;
		t->setGenVarName( var_name );
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_FALSETOKEN) ) {
		_MATCH(TOK_FALSETOKEN);
		f=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_boolean (\"FALSE\")" << endl;
		f->setGenVarName( var_name );
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

void GEN_SOR::enumerator_literal(SORASTBase **_root)
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
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_literal_enum (\"" << edt->getVcharText()
		<< "\", \"" << enum_value->getVcharText()
		<< "\")" << endl;
		edt->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("enumerator_literal", _t);
	}
	*_root = _t;
}

void GEN_SOR::attribute_access(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *irv=NULL;
	SORAST *a=NULL;
	if ( _t!=NULL && (_t->type()==TOK_INST_REF_VAR) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_INST_REF_VAR);
		irv=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_OBJ_ATTR);
		a=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		vchar selected_str1[9];
		vchar selected_str2[9];
		vchar selected_str3[9];
		vcharCopyFromLiteral( "selected", selected_str1 );
		vcharCopyFromLiteral( "Selected", selected_str2 );
		vcharCopyFromLiteral( "SELECTED", selected_str3 );
		if ( vcharCompare( irv->getVcharText(), selected_str1 ) == 0)
		{
			script_var_name var_name;
			get_previous_where ( var_name );
			irv->setGenVarName( var_name );
		}
		else if ( vcharCompare( irv->getVcharText(), selected_str2 ) == 0)
		{
			script_var_name var_name;
			get_previous_where ( var_name );
			irv->setGenVarName( var_name );
		}
		else if ( vcharCompare( irv->getVcharText(), selected_str3 ) == 0)
		{
			script_var_name var_name;
			get_previous_where ( var_name );
			irv->setGenVarName( var_name );
		}
		else
		{
			script_var_name gen_name;
			get_gen_name( irv->getVcharText(), gen_name );
			irv->setGenVarName( gen_name );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("attribute_access", _t);
	}
	*_root = _t;
}

void GEN_SOR::event_data_access(SORASTBase **_root)
{
	SORASTBase *_t = *_root;
	SORAST *re=NULL;
	SORAST *di=NULL;
	if ( _t!=NULL && (_t->type()==TOK_RCVD_EVT) ) {
		_MATCH(TOK_RCVD_EVT);
		re=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_SUPP_DATA_NAME);
		di=(SORAST *)_t;
		_RIGHT;
		
		script_var_name var_name;
		next_rval_var_name ( var_name );
		*out_file << ".Invoke " << var_name
		<< " = rval_read_rcvd_evt_di (" << C_actn_var_name << ", \""
		<< di->getVcharText() << "\")" << endl;
		re->setGenVarName( var_name );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("event_data_access", _t);
	}
	*_root = _t;
}

void GEN_SOR::param_data_access(SORASTBase **_root,  t_boolean is_rval  )
{
	SORASTBase *_t = *_root;
	SORAST *p=NULL;
	SORAST *di=NULL;
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_PARAM) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_BRIDGE_PARAM);
		p=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_DATA_ITEM_NAME);
		di=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		if ( is_rval )
		{
			script_var_name var_name;
			next_rval_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = rval_read_bridge_param (" << C_actn_var_name << ", \""
			<< di->getVcharText() << "\")" << endl;
			p->setGenVarName( var_name );
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_PARAM) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_TRANSFORMER_PARAM);
		p=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_DATA_ITEM_NAME);
		di=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		if ( is_rval )
		{
			script_var_name var_name;
			next_rval_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = rval_read_transform_param (" << C_actn_var_name << ", \""
			<< di->getVcharText() << "\")" << endl;
			p->setGenVarName( var_name );
		}
	}
	else {
	if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_PARAM) ) {
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_SYNCH_SVC_PARAM);
		p=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_DATA_ITEM_NAME);
		di=(SORAST *)_t;
		_RESTORE;
		}
		_RIGHT;
		
		if ( is_rval )
		{
			script_var_name var_name;
			next_rval_var_name ( var_name );
			*out_file << ".Invoke " << var_name
			<< " = rval_read_synch_service_param (" << C_actn_var_name << ", \""
			<< di->getVcharText() << "\")" << endl;
			p->setGenVarName( var_name );
		}
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("param_data_access", _t);
	}
	}
	}
	*_root = _t;
}

void GEN_SOR::transformer_expr(SORASTBase **_root,  vchar **key_lett, vchar **method, bool *instance_based, script_var_name irv_gen_name  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	SORAST *meth=NULL;
	SORAST *di=NULL;
	SORAST *e=NULL;
	SORAST *irv=NULL;
	if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR||_t->type()==TOK_TRANSFORMER_IB_EXPR) ) {
		
		script_var_name var_name1;
		script_var_name var_name2;
		if ( _t!=NULL && (_t->type()==TOK_TRANSFORMER_EXPR) ) {
			{_SAVE; TREE_CONSTR_PTRS;
			_MATCH(TOK_TRANSFORMER_EXPR);
			s=(SORAST *)_t;
			_DOWN;
			_MATCH(TOK_KL_OBJECT);
			kl=(SORAST *)_t;
			_RIGHT;
			_MATCH(TOK_FUNCTION_NAME);
			meth=(SORAST *)_t;
			_RIGHT;
			
			*key_lett = (vchar*) kl->getVcharText();
			*method = (vchar *) meth->getVcharText();
			*instance_based = FALSE;

			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_transform (\"" << kl->getVcharText() << "\", \""
			<< meth->getVcharText() << "\")" << endl ;
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
					{_SAVE; TREE_CONSTR_PTRS;
					_MATCH(TOK_DATA_ITEM_NAME);
					di=(SORAST *)_t;
					_DOWN;
					e=(SORAST *)_t; expr(&_t);
					_RESTORE;
					}
					_RIGHT;
					
					next_param_var_name ( var_name2 );
					*out_file << ".Invoke " << var_name2
					<< " = param_add (" << var_name1 << ", \""
					<< di->getVcharText() << "\", "
					<< e->getGenVarName() << ")" << endl ;
					strcpy ( var_name1, var_name2 );
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
			
			*method = (vchar *) meth->getVcharText();
			*instance_based = TRUE;
			// i2946.1 deleted
			get_gen_name( irv->getVcharText(), irv_gen_name );  // i2946.2.2 changed
			// i2946.1 deleted

			next_param_var_name ( var_name1 );
			*out_file << ".Invoke " << var_name1
			<< " = param_begin_ib_transform (" << irv_gen_name << ", \""  // i2946.1 changed
			<< meth->getVcharText() << "\")" << endl ;
			{int _done=0;
			while ( !_done ) {
				if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
					{_SAVE; TREE_CONSTR_PTRS;
					_MATCH(TOK_DATA_ITEM_NAME);
					di=(SORAST *)_t;
					_DOWN;
					e=(SORAST *)_t; expr(&_t);
					_RESTORE;
					}
					_RIGHT;
					
					next_param_var_name ( var_name2 );
					*out_file << ".Invoke " << var_name2
					<< " = param_add (" << var_name1 << ", \""
					<< di->getVcharText() << "\", "
					<< e->getGenVarName() << ")" << endl ;
					strcpy ( var_name1, var_name2 );
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
		}
		else {
			if ( guessing ) _GUESS_FAIL;
			no_viable_alt("transformer_expr", _t);
		}
		}
		
		next_param_var_name ( var_name2 );
		*out_file << ".Invoke " << var_name2
		<< " = param_end (" << var_name1
		<< ")" << endl ;
		s->setGenVarName( var_name2 );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("transformer_expr", _t);
	}
	*_root = _t;
}

void GEN_SOR::bridge_expr(SORASTBase **_root,  vchar **key_lett, vchar **method  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *kl=NULL;
	SORAST *meth=NULL;
	SORAST *di=NULL;
	SORAST *e=NULL;
	if ( _t!=NULL && (_t->type()==TOK_BRIDGE_EXPR) ) {
		
		script_var_name var_name1;
		script_var_name var_name2;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_BRIDGE_EXPR);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_KL_EXTERNAL_ENTITY);
		kl=(SORAST *)_t;
		_RIGHT;
		_MATCH(TOK_FUNCTION_NAME);
		meth=(SORAST *)_t;
		_RIGHT;
		
		*key_lett = (vchar *) kl->getVcharText();
		*method = (vchar *) meth->getVcharText();

		next_param_var_name ( var_name1 );
		*out_file << ".Invoke " << var_name1
		<< " = param_begin_bridge (\"" << kl->getVcharText() << "\", \""
		<< meth->getVcharText() << "\")" << endl ;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_DATA_ITEM_NAME);
				di=(SORAST *)_t;
				_DOWN;
				e=(SORAST *)_t; expr(&_t);
				_RESTORE;
				}
				_RIGHT;
				
				next_param_var_name ( var_name2 );
				*out_file << ".Invoke " << var_name2
				<< " = param_add (" << var_name1 << ", \""
				<< di->getVcharText() << "\", "
				<< e->getGenVarName() << ")" << endl ;
				strcpy ( var_name1, var_name2 );
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
		
		next_param_var_name ( var_name2 );
		*out_file << ".Invoke " << var_name2
		<< " = param_end (" << var_name1
		<< ")" << endl ;
		s->setGenVarName( var_name2 );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("bridge_expr", _t);
	}
	*_root = _t;
}

void GEN_SOR::synch_svc_expr(SORASTBase **_root,  vchar **method  )
{
	SORASTBase *_t = *_root;
	SORAST *s=NULL;
	SORAST *meth=NULL;
	SORAST *di=NULL;
	SORAST *e=NULL;
	if ( _t!=NULL && (_t->type()==TOK_SYNCH_SVC_EXPR) ) {
		
		script_var_name var_name1;
		script_var_name var_name2;
		{_SAVE; TREE_CONSTR_PTRS;
		_MATCH(TOK_SYNCH_SVC_EXPR);
		s=(SORAST *)_t;
		_DOWN;
		_MATCH(TOK_FUNCTION_NAME);
		meth=(SORAST *)_t;
		_RIGHT;
		
		*method = (vchar *) meth->getVcharText();

		next_param_var_name ( var_name1 );
		*out_file << ".Invoke " << var_name1
		<< " = param_begin_synch_service (\"" 
		<< meth->getVcharText() << "\")" << endl ;
		{int _done=0;
		while ( !_done ) {
			if ( _t!=NULL && (_t->type()==TOK_DATA_ITEM_NAME) ) {
				{_SAVE; TREE_CONSTR_PTRS;
				_MATCH(TOK_DATA_ITEM_NAME);
				di=(SORAST *)_t;
				_DOWN;
				e=(SORAST *)_t; expr(&_t);
				_RESTORE;
				}
				_RIGHT;
				
				next_param_var_name ( var_name2 );
				*out_file << ".Invoke " << var_name2
				<< " = param_add (" << var_name1 << ", \""
				<< di->getVcharText() << "\", "
				<< e->getGenVarName() << ")" << endl ;
				strcpy ( var_name1, var_name2 );
			}
			else {
			if ( _t==NULL ) {
				_done = 1;
			}
			else {
				if ( guessing ) _GUESS_FAIL;
				no_viable_alt("synch_svc_expr", _t);
			}
			}
		}
		}
		_RESTORE;
		}
		_RIGHT;
		
		next_param_var_name ( var_name2 );
		*out_file << ".Invoke " << var_name2
		<< " = param_end (" << var_name1
		<< ")" << endl ;
		s->setGenVarName( var_name2 );
	}
	else {
		if ( guessing ) _GUESS_FAIL;
		no_viable_alt("synch_svc_expr", _t);
	}
	*_root = _t;
}

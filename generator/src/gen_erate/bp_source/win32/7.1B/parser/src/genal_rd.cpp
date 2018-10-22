/*========================================================================
 *
 * File:      $RCSfile: genal_rd.cpp,v $
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
#include "GEN_SOR.h"
#include "vchar.h"

#include "gs_sizes.hh"    // GS_STACK_SIZE
#include "p_swhere.hh"

struct stack_entry {
  vchar var_name[256];
  vchar obj_kl[64];        // HACK - What's the real constant to use here?
  script_var_name gen_name;
  bool declared;
};

static stack_entry  G_stack[GS_STACK_SIZE];
static int G_stack_ptr = 0;

#define CTRL_ENTRY "NEWS"

void GEN_SOR::new_scope()
{
  if ( G_stack_ptr >= GS_STACK_SIZE )
  {
    // HACK - need an error message here....
    puts("Internal error: stack overflow"); 
  }
  else
  {
    vcharCopyFromLiteral (CTRL_ENTRY, G_stack[G_stack_ptr].var_name);
    G_stack_ptr += 1;

    script_var_name blck1;
    next_blck_var_name ( blck1 );
    *out_file << ".Invoke " << blck1 << " = blck_begin ()" << endl;
  }
}

void GEN_SOR::drop_scope()
{

  vchar ctrl_entry[5];
  vcharCopyFromLiteral ( CTRL_ENTRY, ctrl_entry );
  while ( G_stack_ptr > 1 && 
          vcharCompare(G_stack[G_stack_ptr-1].var_name, ctrl_entry) != 0 )
    G_stack_ptr -= 1;

  script_var_name last_blck;
  get_previous_block ( last_blck );
  script_var_name blckn;
  next_blck_var_name ( blckn );
  *out_file << ".Invoke " << blckn << " = blck_end (" << last_blck << ")" << endl;

  // then pop the CTRL_ENTRY
  if ( G_stack_ptr >= 1 )
    G_stack_ptr -= 1;

}

void GEN_SOR::get_previous_block(script_var_name var_name)
{
  sprintf (var_name, "b%03d", blck_inst_num-1);
}

void GEN_SOR::get_previous_where(script_var_name var_name)
{
  sprintf (var_name, "w%03d", where_inst_num-1);
}

void GEN_SOR::get_previous_param(script_var_name var_name)
{
  sprintf (var_name, "p%03d", param_inst_num-1);
}

void GEN_SOR::add_var_to_scope(const vchar *var_name, const vchar *obj_kl, script_var_name gen_name)
{

  if ( G_stack_ptr >= GS_STACK_SIZE )
  {
    // HACK - need an error message here....
    puts("Internal error: stack overflow"); 
  }
  else
  {
    // the only reason I need the obj_kl is for implicit decl's of
    // the loop variable of a for statement

    vcharCopy(var_name, G_stack[G_stack_ptr].var_name);
    vcharCopy(obj_kl, G_stack[G_stack_ptr].obj_kl);
    strcpy (G_stack[G_stack_ptr].gen_name, gen_name);
    G_stack[G_stack_ptr].declared = FALSE;
    G_stack_ptr += 1;
  }
}

void GEN_SOR::delete_all_var_from_scope()
{
  script_var_name prev_blck;   
  script_var_name blckn;

  vchar ctrl_entry[5];
  vcharCopyFromLiteral ( CTRL_ENTRY, ctrl_entry );
  while ( G_stack_ptr > 0 && 
          vcharCompare (G_stack[G_stack_ptr-1].var_name, ctrl_entry) != 0 )
  {
    get_previous_block ( prev_blck ); 
    next_blck_var_name ( blckn );
    *out_file << ".Invoke " << blckn << " = blck_var_out_of_scope (" 
             << prev_blck << ", " 
             << G_stack[G_stack_ptr-1].gen_name << ")" << endl;
    G_stack_ptr -= 1;
  }
}

bool GEN_SOR::is_var_declared_in_scope(const vchar *var_name)
{
  int l_stack_ptr = G_stack_ptr - 1;
  while ( l_stack_ptr >= 0  )
    if ( vcharCompare (G_stack[l_stack_ptr].var_name, var_name) == 0 )
      return G_stack[l_stack_ptr].declared ;
    else
      l_stack_ptr -= 1;

  return FALSE;
}

bool GEN_SOR::is_var_in_scope(const vchar *var_name)
{
  int l_stack_ptr = G_stack_ptr - 1;
  while ( l_stack_ptr >= 0  )
    if ( vcharCompare (G_stack[l_stack_ptr].var_name, var_name) == 0 )
      return TRUE;
    else
      l_stack_ptr -= 1;

  return FALSE;
}

bool GEN_SOR::is_selected ( script_var_name x )
{
  // If the gen_var_name starts with a 'w', then the 
  // inst ref var was 'selected'
  return x[0] == 'w';
}

vchar * GEN_SOR::get_key_letters(const vchar *var_name)
{
  int l_stack_ptr = G_stack_ptr - 1;
  while ( l_stack_ptr >= 0  )
    if ( vcharCompare (G_stack[l_stack_ptr].var_name, var_name) == 0 )
      return G_stack[l_stack_ptr].obj_kl ;
    else
      l_stack_ptr -= 1;

  return 0;
}

void GEN_SOR::set_var_declared_in_scope(const vchar *var_name)
{
  int l_stack_ptr = G_stack_ptr - 1;
  while ( l_stack_ptr >= 0  )
    if ( vcharCompare (G_stack[l_stack_ptr].var_name, var_name) == 0 )
    {
      G_stack[l_stack_ptr].declared = TRUE;
      break;
    }
    else
      l_stack_ptr -= 1;

//  *out_file << ".// set_var_declared_in_scope - " << var_name << endl;
}

void GEN_SOR::get_gen_name(const vchar *var_name, script_var_name gen_name)
{
  strcpy ( gen_name, "ERR1" );
  int l_stack_ptr = G_stack_ptr - 1;
  while ( l_stack_ptr >= 0  )
    if ( vcharCompare (G_stack[l_stack_ptr].var_name, var_name) == 0 )
    {
      strcpy ( gen_name, G_stack[l_stack_ptr].gen_name );
      break;
    }
    else
      l_stack_ptr -= 1;
}

void GEN_SOR::add_valid_statement( script_var_name var_name )
{
  if ( strcmp ( var_name, "DONT" ) != 0 )
  {
    script_var_name blckn, prev_blck;
    get_previous_block ( prev_blck );
    next_blck_var_name ( blckn );
    *out_file << ".Invoke " << blckn << " = blck_append_stmt ("
             << prev_blck << ", "
             << var_name << ")" << endl;
  }
}

void GEN_SOR::declare_oir ( script_var_name var_name, 
                            const vchar *oir_name, const vchar *obj_kl )
{
  *out_file << ".Invoke " << var_name << " = var_declare_obj_inst_ref (\""
           << oir_name  << "\", \""
           << obj_kl << "\")" << endl;
}

void GEN_SOR::declare_oirs ( script_var_name var_name, 
                            const vchar *oirs_name, const vchar *obj_kl )
{
  *out_file << ".Invoke " << var_name << " = var_declare_obj_inst_ref_set (\""
           << oirs_name  << "\", \""
           << obj_kl << "\")" << endl;
}

void GEN_SOR::declare_ei ( script_var_name var_name, 
                            const vchar *ei_name )
{
  *out_file << ".Invoke " << var_name << " = var_declare_evt_inst_ref (\""
           << ei_name  << "\")" << endl;
}

void GEN_SOR::special_where_invokes( Special_Where *sw )
{
  script_var_name param1;
  next_param_var_name(param1);
  *out_file << ".Invoke " << param1 << " = param_begin_where_special (\""
           << sw->key  << "\")" << endl;

  script_var_name paramn, prev_param;
  strcpy ( prev_param, param1 );

  // for each qmark in sw
  AST *qmark = sw->parsed_where->ttqm->getItemHead();
  int qmark_num = 1;
  while ( qmark )
  {
    // objPtr points to corresponding expression in where clause
    // This is how the code must be written to work properly.
    // Otherwise se->getGenVarName() is empty.
    SORASTBase *p_sub_expr = (ASTBase *) qmark->getObjPtr();
    SORAST *se = (SORAST *) p_sub_expr;
    GEN_SOR::sub_expr( &p_sub_expr );
    next_param_var_name(paramn);

    *out_file << ".Invoke " << paramn << " = param_add ("
             << prev_param  << ", \""
             << qmark_num << "\", "
             << se->getGenVarName() << ")" << endl;
  
    strcpy ( prev_param, paramn );

    qmark_num += 1;
    qmark = qmark->getItemNext();
  }  

  next_param_var_name(paramn);
  *out_file << ".Invoke " << paramn << " = param_end ("
           << prev_param  << ")" << endl;

}

void GEN_SOR::mismatched_range(int looking_for, 
        int upper_token, SORASTBase *found)
{
  P_error* er = parser->er;
  if ( found == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR2( c_ast, AL_GETMSG(ERR,356,2), looking_for, upper_token )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)found;
    AL_PARSE_ERR3( c_ast, AL_GETMSG(ERR,357,3), looking_for, upper_token, found->type() )
  }
}

void GEN_SOR::missing_wildcard()
{
  P_error* er = parser->er;
  AST *c_ast = (new AST(TOK_GARBAGE));
  AL_PARSE_ERR0( c_ast, AL_GETMSG(ERR,358,0))
  delete c_ast;
}

void GEN_SOR::mismatched_token(int looking_for, SORASTBase *found)
{
  P_error* er = parser->er;
  if ( found == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,359,1), looking_for )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)found;
    AL_PARSE_ERR2( c_ast, AL_GETMSG(ERR,360,2), looking_for, found->type() )
  }
}

void GEN_SOR::no_viable_alt(char *rulename, SORASTBase *root)
{
  P_error* er = parser->er;
  if ( root == NULL )
  {
    AST *c_ast = (new AST(TOK_GARBAGE));
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,361,1), vcharScribeASCII(rulename) )
    delete c_ast;
  }
  else
  {
    AST *c_ast = (AST*)root;
    AL_PARSE_ERR1( c_ast, AL_GETMSG(ERR,362,1), vcharScribeASCII(rulename) )
  }
}

